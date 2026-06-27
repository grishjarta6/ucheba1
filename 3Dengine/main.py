import sys
import math
import time
import threading
import queue

# --------------------- constants ---------------------
SCREEN_WIDTH = 120
SCREEN_HEIGHT = 40
FOV = math.pi / 3               # 60 degrees
HALF_FOV = FOV / 2
MAX_DEPTH = 25.0
GRAVITY = -9.81                 # units/s² down
FRAME_DT = 1 / 30               # desired frame time
PLAYER_EYE_HEIGHT = 0.6         # eye above ground

# shading: distance -> (character, ansi-colour)
SHADE_LEVELS = [
    (2.0,  '█', '97'),   # bright white
    (5.0,  '▓', '37'),   # white
    (8.0,  '▒', '90'),   # bright black (gray)
    (12.0, '░', '90'),
    (16.0, '.', '90'),
    (20.0, ' ', '0')     # invisible
]
# ansi colour helpers
def ansi_fg(col):
    return f'\033[38;5;{col}m'
def ansi_reset():
    return '\033[0m'

def shade_for_dist(dist):
    """return (char, ansi_fg_code) for given perpendicular distance"""
    for max_d, ch, col in SHADE_LEVELS:
        if dist <= max_d:
            return ch, col
    return ' ', '0'

# --------------------- map ---------------------
class Map:
    def __init__(self, filename):
        with open(filename, 'r') as f:
            lines = [line.rstrip('\n') for line in f if line.strip() != '']
        self.height = len(lines)
        self.width = max(len(line) for line in lines)
        self.grid = []
        self.floor_z = []      # floor height of each cell
        self.ceiling_z = []    # ceiling height
        self.stairs_up = []    # bool
        self.stairs_down = []
        for y in range(self.height):
            row = []
            fz_row = []
            cz_row = []
            su_row = []
            sd_row = []
            for x in range(self.width):
                ch = lines[y][x] if x < len(lines[y]) else ' '
                row.append(ch)
                # default floor 0, ceiling 2
                fz = 0.0
                cz = 2.0
                su = False
                sd = False
                if ch == '#' or ch == 'D':   # solid wall
                    fz = 0.0
                    cz = 2.0
                elif ch == '^':               # stairs up
                    su = True
                    fz = 1.0                  # raised floor
                    cz = 3.0
                elif ch == 'v':               # stairs down
                    sd = True
                    fz = -1.0
                    cz = 1.0
                # other: floor, keep default
                fz_row.append(fz)
                cz_row.append(cz)
                su_row.append(su)
                sd_row.append(sd)
            self.grid.append(row)
            self.floor_z.append(fz_row)
            self.ceiling_z.append(cz_row)
            self.stairs_up.append(su_row)
            self.stairs_down.append(sd_row)

    def is_wall(self, x, y):
        if x < 0 or y < 0 or x >= self.width or y >= self.height:
            return True
        ch = self.grid[y][x]
        return ch in ('#', 'D')

    def wall_height(self, x, y):
        """height of wall block (top - bottom)"""
        if self.is_wall(x, y):
            return self.ceiling_z[y][x] - self.floor_z[y][x]
        return 0.0

    def floor_at(self, x, y):
        if 0 <= x < self.width and 0 <= y < self.height:
            return self.floor_z[y][x]
        return 0.0

    def is_stairs_up(self, x, y):
        if 0 <= x < self.width and 0 <= y < self.height:
            return self.stairs_up[y][x]
        return False

    def is_stairs_down(self, x, y):
        if 0 <= x < self.width and 0 <= y < self.height:
            return self.stairs_down[y][x]
        return False

# --------------------- vector math ---------------------
def rotate_vec(x, y, angle):
    c = math.cos(angle)
    s = math.sin(angle)
    return x * c - y * s, x * s + y * c

# --------------------- game object ---------------------
class GameObject:
    def __init__(self, x, y, z, char, color, health=1):
        self.x = x
        self.y = y
        self.z = z
        self.vx = 0.0
        self.vy = 0.0
        self.vz = 0.0
        self.char = char
        self.color = color
        self.health = health
        self.alive = True
        self.radius = 0.3          # for collision / interaction

    def update(self, dt, game_map, all_objects):
        """physics + interactions. returns list of events"""
        # gravity
        self.vz += GRAVITY * dt
        # movement
        new_x = self.x + self.vx * dt
        new_y = self.y + self.vy * dt
        new_z = self.z + self.vz * dt

        # simple collision with walls (2D)
        if not game_map.is_wall(int(new_x), int(self.y)):
            self.x = new_x
        if not game_map.is_wall(int(self.x), int(new_y)):
            self.y = new_y

        # vertical collision: floor
        floor_h = game_map.floor_at(int(self.x), int(self.y))
        if new_z < floor_h:
            self.z = floor_h
            self.vz = 0
        else:
            self.z = new_z

        # check if dead (fell off map)
        if self.z < -10:
            self.alive = False

        # stair interactions: change player z (handled in player logic)
        # here just for generic objects we don't use stairs.

        # interactions with other objects
        events = []
        for other in all_objects:
            if other is self or not other.alive:
                continue
            dx = self.x - other.x
            dy = self.y - other.y
            dz = self.z - other.z
            dist = math.sqrt(dx*dx + dy*dy + dz*dz)
            if dist < self.radius + other.radius:
                # collision: simple damage transfer (e.g., projectile vs enemy)
                if hasattr(self, 'damage') and self.damage > 0:
                    other.health -= self.damage
                    events.append(f'{other.char} takes {self.damage} damage')
                    self.alive = False   # projectile disappears
                # bounce: simple
                if self.vx or self.vy:
                    # push apart
                    pass
        return events

# --------------------- camera ---------------------
class Camera:
    def __init__(self, x, y, z, angle):
        self.x = x
        self.y = y
        self.z = z
        self.angle = angle
        self.pitch = 0.0   # looking straight ahead

# --------------------- ray casting ---------------------
def cast_ray(cam, game_map, screen_x):
    """cast a ray for column screen_x, return (perp_dist, wall_height, side)"""
    ray_angle = cam.angle + math.atan((2 * screen_x / SCREEN_WIDTH - 1) * math.tan(HALF_FOV))
    ray_dir_x = math.cos(ray_angle)
    ray_dir_y = math.sin(ray_angle)

    # DDA
    map_x = int(cam.x)
    map_y = int(cam.y)
    delta_dist_x = abs(1 / (ray_dir_x + 1e-10))
    delta_dist_y = abs(1 / (ray_dir_y + 1e-10))

    if ray_dir_x < 0:
        step_x = -1
        side_dist_x = (cam.x - map_x) * delta_dist_x
    else:
        step_x = 1
        side_dist_x = (map_x + 1.0 - cam.x) * delta_dist_x

    if ray_dir_y < 0:
        step_y = -1
        side_dist_y = (cam.y - map_y) * delta_dist_y
    else:
        step_y = 1
        side_dist_y = (map_y + 1.0 - cam.y) * delta_dist_y

    hit = False
    side = 0
    while not hit:
        if side_dist_x < side_dist_y:
            side_dist_x += delta_dist_x
            map_x += step_x
            side = 0
        else:
            side_dist_y += delta_dist_y
            map_y += step_y
            side = 1
        if game_map.is_wall(map_x, map_y):
            hit = True

    if side == 0:
        perp_dist = (map_x - cam.x + (1 - step_x) / 2) / (ray_dir_x + 1e-10)
    else:
        perp_dist = (map_y - cam.y + (1 - step_y) / 2) / (ray_dir_y + 1e-10)

    wall_h = game_map.wall_height(map_x, map_y)
    return perp_dist, wall_h, side

# --------------------- rendering ---------------------
def render_frame(cam, game_map, objects, screen_buf, z_buffer):
    """fill screen_buf (list of strings) and z_buffer with distances"""
    # clear
    for y in range(SCREEN_HEIGHT):
        screen_buf[y] = [' '] * SCREEN_WIDTH
        z_buffer[y] = [MAX_DEPTH] * SCREEN_WIDTH

    # ceiling / floor background (simple)
    for y in range(SCREEN_HEIGHT):
        if y < SCREEN_HEIGHT/2:
            char = '·'
            col = '34'   # blue
        else:
            char = '~'
            col = '32'   # green
        for x in range(SCREEN_WIDTH):
            screen_buf[y][x] = f'{ansi_fg(col)}{char}{ansi_reset()}'

    # cast walls
    for x in range(SCREEN_WIDTH):
        perp_dist, wall_h, side = cast_ray(cam, game_map, x)
        if perp_dist <= 0:
            perp_dist = 0.01
        # projection
        scale = SCREEN_HEIGHT / perp_dist
        eye_z = cam.z + PLAYER_EYE_HEIGHT
        wall_top = SCREEN_HEIGHT/2 - (wall_h - eye_z) * scale
        wall_bot = SCREEN_HEIGHT/2 - (0 - eye_z) * scale

        # shading
        shade_char, shade_col = shade_for_dist(perp_dist)
        if side == 1:   # y-side, slightly darker
            shade_col = '90' if shade_col == '37' else shade_col

        # clamp to screen
        top = max(0, int(wall_top))
        bot = min(SCREEN_HEIGHT-1, int(wall_bot))
        for y in range(top, bot+1):
            screen_buf[y][x] = f'{ansi_fg(shade_col)}{shade_char}{ansi_reset()}'
            z_buffer[y][x] = perp_dist   # store for sprite clipping

    # sprites (objects)
    sprite_list = []
    for obj in objects:
        if not obj.alive:
            continue
        # vector from camera to object
        dx = obj.x - cam.x
        dy = obj.y - cam.y
        # transform to camera space
        inv_angle = -cam.angle
        tx, ty = rotate_vec(dx, dy, inv_angle)
        if tx <= 0:
            continue   # behind
        # perspective projection
        sprite_screen_x = int((SCREEN_WIDTH/2) * (1 + ty / tx / math.tan(HALF_FOV)))
        sprite_height = int(SCREEN_HEIGHT / tx)   # object height in pixels
        dz = obj.z - cam.z
        sprite_screen_y = int(SCREEN_HEIGHT/2 - (dz - PLAYER_EYE_HEIGHT) * SCREEN_HEIGHT / tx)

        sprite_list.append((tx, sprite_screen_x, sprite_height, sprite_screen_y, obj))

    # sort far to near
    sprite_list.sort(key=lambda s: s[0], reverse=True)

    for _, sx, sh, sy, obj in sprite_list:
        # clipping
        draw_start_x = max(0, sx - sh//2)
        draw_end_x = min(SCREEN_WIDTH-1, sx + sh//2)
        draw_start_y = max(0, sy - sh//2)
        draw_end_y = min(SCREEN_HEIGHT-1, sy + sh//2)

        for x in range(draw_start_x, draw_end_x+1):
            if x < 0 or x >= SCREEN_WIDTH:
                continue
            # check depth buffer
            if z_buffer[draw_start_y][x] < obj.x - cam.x:   # approximate
                continue
            for y in range(draw_start_y, draw_end_y+1):
                if y < 0 or y >= SCREEN_HEIGHT:
                    continue
                # distance based fading
                dist = math.sqrt((obj.x-cam.x)**2 + (obj.y-cam.y)**2)
                _, col = shade_for_dist(dist)
                screen_buf[y][x] = f'{ansi_fg(col)}{obj.char}{ansi_reset()}'

def display(screen_buf):
    """print whole screen buffer with ANSI clear"""
    sys.stdout.write('\033[2J\033[H')   # clear screen, home
    for row in screen_buf:
        sys.stdout.write(''.join(row) + '\n')
    sys.stdout.flush()

# --------------------- input thread ---------------------
input_queue = queue.Queue()

def input_reader():
    while True:
        try:
            line = sys.stdin.readline()
            if not line:
                break
            cmd = line.strip().lower()
            input_queue.put(cmd)
        except:
            break

# --------------------- main game loop ---------------------
def main():
    # load map
    try:
        game_map = Map('level.txt')
    except FileNotFoundError:
        print("level.txt not found. Creating a default one.")
        with open('level.txt', 'w') as f:
            f.write("####################\n")
            f.write("#   ^    #    v   #\n")
            f.write("#   #         #   #\n")
            f.write("#        #        #\n")
            f.write("#   D    #    D   #\n")
            f.write("####################\n")
        game_map = Map('level.txt')

    # camera start position
    cam = Camera(x=1.5, y=1.5, z=0.0, angle=0.0)

    # objects: enemy and projectiles
    enemy = GameObject(5.0, 1.5, 0.0, 'E', '196', health=3)  # red-ish
    objects = [enemy]
    player_bullets = []   # separate list for projectiles

    # screen buffers
    screen_buf = [[' ']*SCREEN_WIDTH for _ in range(SCREEN_HEIGHT)]
    z_buffer = [[MAX_DEPTH]*SCREEN_WIDTH for _ in range(SCREEN_HEIGHT)]

    # start input thread
    input_thread = threading.Thread(target=input_reader, daemon=True)
    input_thread.start()

    # timings
    last_time = time.time()
    running = True

    while running:
        # process input commands
        while not input_queue.empty():
            cmd = input_queue.get_nowait()
            if cmd == 'quit':
                running = False
                break
            elif cmd == 'w':
                # move forward
                dx = math.cos(cam.angle) * 0.2
                dy = math.sin(cam.angle) * 0.2
                new_x = cam.x + dx
                new_y = cam.y + dy
                if not game_map.is_wall(int(new_x), int(new_y)):
                    cam.x = new_x
                    cam.y = new_y
            elif cmd == 's':
                dx = -math.cos(cam.angle) * 0.2
                dy = -math.sin(cam.angle) * 0.2
                new_x = cam.x + dx
                new_y = cam.y + dy
                if not game_map.is_wall(int(new_x), int(new_y)):
                    cam.x = new_x
                    cam.y = new_y
            elif cmd == 'a':
                # strafe left
                dx = -math.sin(cam.angle) * 0.2
                dy = math.cos(cam.angle) * 0.2
                new_x = cam.x + dx
                new_y = cam.y + dy
                if not game_map.is_wall(int(new_x), int(new_y)):
                    cam.x = new_x
                    cam.y = new_y
            elif cmd == 'd':
                dx = math.sin(cam.angle) * 0.2
                dy = -math.cos(cam.angle) * 0.2
                new_x = cam.x + dx
                new_y = cam.y + dy
                if not game_map.is_wall(int(new_x), int(new_y)):
                    cam.x = new_x
                    cam.y = new_y
            elif cmd == 'e':
                cam.angle += 0.1
            elif cmd == 'q':
                cam.angle -= 0.1
            elif cmd == ' ':
                # jump
                if cam.z <= game_map.floor_at(int(cam.x), int(cam.y)) + 0.01:
                    cam.vz = 3.0   # upward velocity
                    cam.z += 0.01  # unstick
            elif cmd == 'f':
                # shoot projectile from camera
                bullet = GameObject(cam.x, cam.y, cam.z + PLAYER_EYE_HEIGHT,
                                    '*', '226', health=1)
                bullet.damage = 1
                speed = 8.0
                bullet.vx = math.cos(cam.angle) * speed
                bullet.vy = math.sin(cam.angle) * speed
                bullet.vz = 0.0
                bullet.radius = 0.1
                player_bullets.append(bullet)
                objects.append(bullet)

        # timing
        current_time = time.time()
        dt = current_time - last_time
        if dt < FRAME_DT:
            time.sleep(FRAME_DT - dt)
            current_time = time.time()
            dt = current_time - last_time
        last_time = current_time

        if not running:
            break

        # update player physics (gravity)
        cam.vz += GRAVITY * dt if hasattr(cam, 'vz') else 0
        if not hasattr(cam, 'vz'):
            cam.vz = 0.0
        new_z = cam.z + cam.vz * dt
        floor_h = game_map.floor_at(int(cam.x), int(cam.y))
        if new_z < floor_h:
            cam.z = floor_h
            cam.vz = 0
        else:
            cam.z = new_z

        # check stairs
        if game_map.is_stairs_up(int(cam.x), int(cam.y)):
            cam.z += 1.0   # teleport up
        elif game_map.is_stairs_down(int(cam.x), int(cam.y)):
            cam.z -= 1.0

        # update objects
        all_objs = objects + player_bullets
        for obj in all_objs:
            if obj.alive:
                events = obj.update(dt, game_map, all_objs)
                for ev in events:
                    # could print messages later
                    pass

        # remove dead objects
        objects = [obj for obj in objects if obj.alive]
        player_bullets = [b for b in player_bullets if b.alive]

        # simple enemy AI: move toward player slowly
        if enemy.alive:
            dx = cam.x - enemy.x
            dy = cam.y - enemy.y
            dist = math.sqrt(dx*dx+dy*dy)
            if dist > 1.0:
                speed = 1.0
                enemy.vx = (dx/dist) * speed
                enemy.vy = (dy/dist) * speed
            else:
                enemy.vx = enemy.vy = 0.0

        # render
        render_frame(cam, game_map, objects, screen_buf, z_buffer)
        display(screen_buf)

    # cleanup
    sys.stdout.write('\033[2J\033[H')
    sys.stdout.write('Game exited.\n')

if __name__ == '__main__':
    main()
