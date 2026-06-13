#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cmath>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <map>

using namespace std;

// ========== Параметры экрана и мира ==========
const int SCREEN_WIDTH  = 120;
const int SCREEN_HEIGHT = 40;
const float PI          = 3.14159265358979f;
const float FOV         = PI / 3.0f;          // горизонтальный угол обзора
const float VERTICAL_FOV = PI / 3.0f;         // вертикальный угол обзора
const float EYE_HEIGHT   = 0.5f;              // высота камеры над полом
const float CEILING_HEIGHT = 1.0f;            // высота потолка
const float GRAVITY       = 15.0f;            // ускорение свободного падения
const float PLAYER_SPEED  = 3.0f;
const float PLAYER_ROT_SPEED = 2.0f;
const float PROJECTILE_SPEED = 10.0f;
const float LIGHT_FALLOFF_WALL   = 0.15f;
const float LIGHT_FALLOFF_FLOOR  = 0.1f;

// ========== Вспомогательные структуры ==========
struct Vec2 { float x, y; };
struct Vec3 { float r, g, b; };

// ========== ANSI‑управление консолью ==========
void clearScreen() {
    cout << "\033[2J\033[H";
}
void gotoxy(int x, int y) {
    cout << "\033[" << y << ";" << x << "H";
}
void setBackground(int r, int g, int b) {
    // clamp
    if (r < 0) r = 0; if (r > 255) r = 255;
    if (g < 0) g = 0; if (g > 255) g = 255;
    if (b < 0) b = 0; if (b > 255) b = 255;
    cout << "\033[48;2;" << r << ";" << g << ";" << b << "m";
}
void setForeground(int r, int g, int b) {
    if (r < 0) r = 0; if (r > 255) r = 255;
    if (g < 0) g = 0; if (g > 255) g = 255;
    if (b < 0) b = 0; if (b > 255) b = 255;
    cout << "\033[38;2;" << r << ";" << g << ";" << b << "m";
}
void resetColor() {
    cout << "\033[0m";
}

// ========== Типы стен ==========
struct WallType {
    Vec3 color;
};
map<char, WallType> wallTypes;

void initWallTypes() {
    wallTypes['#'] = { { 128, 128, 128 } };   // серая стена
    wallTypes['D'] = { { 139, 69, 19 } };     // коричневая
    wallTypes['='] = { { 100, 100, 100 } };   // ещё одна
}

// ========== Карта уровня ==========
class Map {
public:
    vector<string> grid;
    int width, height;

    Map(const string& filename) {
        ifstream file(filename);
        string line;
        while (getline(file, line)) {
            grid.push_back(line);
        }
        height = (int)grid.size();
        width  = (height > 0) ? (int)grid[0].length() : 0;
    }

    char getCell(int x, int y) const {
        if (x < 0 || x >= width || y < 0 || y >= height) return '#';
        return grid[y][x];
    }

    bool isWall(int x, int y) const {
        char c = getCell(x, y);
        return wallTypes.find(c) != wallTypes.end();
    }

    WallType getWallType(int x, int y) const {
        char c = getCell(x, y);
        auto it = wallTypes.find(c);
        if (it != wallTypes.end()) return it->second;
        return { {200,200,200} };
    }
};

// ========== Трассировка луча (DDA) ==========
struct HitInfo {
    float perpDist;
    int mapX, mapY;
    int side;          // 0 – вертикальная грань, 1 – горизонтальная
    WallType wall;
};

HitInfo castRay(const Map& map, float playerX, float playerY, float rayAngle) {
    float dirX = cos(rayAngle);
    float dirY = sin(rayAngle);

    int mapX = int(playerX);
    int mapY = int(playerY);

    float deltaDistX = fabs(1.0f / dirX);
    float deltaDistY = fabs(1.0f / dirY);

    float sideDistX, sideDistY;
    int stepX, stepY;

    if (dirX < 0) { stepX = -1; sideDistX = (playerX - mapX) * deltaDistX; }
    else          { stepX =  1; sideDistX = (mapX + 1.0f - playerX) * deltaDistX; }

    if (dirY < 0) { stepY = -1; sideDistY = (playerY - mapY) * deltaDistY; }
    else          { stepY =  1; sideDistY = (mapY + 1.0f - playerY) * deltaDistY; }

    bool hit = false;
    int side;
    while (!hit) {
        if (sideDistX < sideDistY) {
            sideDistX += deltaDistX;
            mapX += stepX;
            side = 0;
        } else {
            sideDistY += deltaDistY;
            mapY += stepY;
            side = 1;
        }
        if (map.isWall(mapX, mapY)) hit = true;
    }

    float perpDist;
    if (side == 0)
        perpDist = (mapX - playerX + (1.0f - stepX) / 2.0f) / dirX;
    else
        perpDist = (mapY - playerY + (1.0f - stepY) / 2.0f) / dirY;

    HitInfo info;
    info.perpDist = perpDist;
    info.mapX = mapX;
    info.mapY = mapY;
    info.side = side;
    info.wall = map.getWallType(mapX, mapY);
    return info;
}

// ========== Таблица тангенсов для пола/потолка ==========
float tanTable[SCREEN_HEIGHT];

void initTanTable() {
    float halfH = SCREEN_HEIGHT / 2.0f;
    for (int y = 0; y < SCREEN_HEIGHT; y++) {
        float angle = ((y - halfH) / halfH) * (VERTICAL_FOV / 2.0f);
        tanTable[y] = tan(angle);
    }
}

// ========== Освещение (фонарик) ==========
float lightFactorWall(float dist) {
    if (dist <= 0.0f) return 1.0f;
    float f = 1.0f / (1.0f + dist * LIGHT_FALLOFF_WALL);
    if (f < 0.0f) f = 0.0f;
    if (f > 1.0f) f = 1.0f;
    return f;
}
float lightFactorFloor(float dist) {
    if (dist <= 0.0f) return 1.0f;
    float f = 1.0f / (1.0f + dist * LIGHT_FALLOFF_FLOOR);
    if (f < 0.0f) f = 0.0f;
    if (f > 1.0f) f = 1.0f;
    return f;
}

// ========== Объекты (базовый класс) ==========
class Object {
public:
    float x, y, z;        // z – высота над полом
    float vx, vy, vz;
    float radius;
    char spriteChar;
    Vec3 color;
    int health;
    bool active;

    Object(float x_, float y_, char ch, Vec3 col, float rad = 0.3f)
        : x(x_), y(y_), z(0.0f), vx(0), vy(0), vz(0),
          radius(rad), spriteChar(ch), color(col), health(1), active(true) {}

    virtual ~Object() {}

    virtual void Update(float dt) {
        vz -= GRAVITY * dt;
        x += vx * dt;
        y += vy * dt;
        z += vz * dt;
        if (z < 0.0f) { z = 0.0f; vz = 0.0f; }
    }
};

// ========== Игрок (управляется с клавиатуры) ==========
class Player : public Object {
public:
    float angle;

    Player(float x_, float y_, float ang_)
        : Object(x_, y_, 'P', {255,255,0}, 0.2f), angle(ang_) {
        z = 0.0f; // камера всегда на полу
    }

    void Update(float dt) override {
        // Гравитация на игрока не действует
        x += vx * dt;
        y += vy * dt;
        // wall collision разрешается отдельно в main
    }
};

// ========== Снаряд ==========
class Projectile : public Object {
public:
    Projectile(float x_, float y_, float z_, float direction)
        : Object(x_, y_, '*', {255,255,0}, 0.1f) {
        z = z_;
        vx = cos(direction) * PROJECTILE_SPEED;
        vy = sin(direction) * PROJECTILE_SPEED;
        vz = 0.0f;
    }

    void Update(float dt) override {
        Object::Update(dt);
        // снаряд будет удалён при столкновении со стеной в main
    }
};

// ========== Главный цикл ==========
int main() {
    // ---------- инициализация ----------
    initWallTypes();
    initTanTable();
    Map map("map.txt");   // файл с картой должен существовать

    Player player(2.5f, 2.5f, 0.0f);
    vector<Object*> objects;

    // несколько статических объектов
    objects.push_back(new Object(4.0f, 3.0f, 'M', {255,0,0}, 0.3f));
    objects.push_back(new Object(6.0f, 5.0f, 'B', {0,255,0}, 0.3f));

    float dt = 0.05f;       // фиксированный шаг на кадр
    float focalLen = (SCREEN_HEIGHT / 2.0f) / tan(VERTICAL_FOV / 2.0f);
    float zBuffer[SCREEN_WIDTH];
    bool running = true;

    // ---------- игровой цикл ----------
    while (running) {
        // 1. Очистка и заливка пола / потолка
        clearScreen();
        for (int y = 0; y < SCREEN_HEIGHT; y++) {
            int halfH = SCREEN_HEIGHT / 2;
            float rowDist;
            Vec3 baseColor;
            if (y > halfH) {   // пол
                float tanVal = tanTable[y];
                if (fabs(tanVal) < 0.0001f) tanVal = 0.0001f;
                rowDist = EYE_HEIGHT / tanVal;
                baseColor = { 80, 80, 80 };
            } else {           // потолок
                float tanVal = -tanTable[y];
                if (tanVal < 0.0001f) tanVal = 0.0001f;
                rowDist = (CEILING_HEIGHT - EYE_HEIGHT) / tanVal;
                baseColor = { 60, 60, 100 };
            }
            float light = lightFactorFloor(rowDist);
            int r = int(baseColor.r * light);
            int g = int(baseColor.g * light);
            int b = int(baseColor.b * light);
            setBackground(r, g, b);
            gotoxy(1, y + 1);
            for (int i = 0; i < SCREEN_WIDTH; i++) cout << ' ';
        }
        resetColor();

        // 2. Стены
        for (int x = 0; x < SCREEN_WIDTH; x++) {
            float rayAngle = player.angle - FOV/2.0f +
                             (x / (float)SCREEN_WIDTH) * FOV;
            HitInfo hit = castRay(map, player.x, player.y, rayAngle);
            zBuffer[x] = hit.perpDist;

            int lineHeight = (int)(SCREEN_HEIGHT / hit.perpDist);
            int wallTop    = max(0, (SCREEN_HEIGHT - lineHeight) / 2);
            int wallBottom = min(SCREEN_HEIGHT - 1, wallTop + lineHeight - 1);

            float light = lightFactorWall(hit.perpDist);
            Vec3 col = hit.wall.color;
            int r = int(col.r * light);
            int g = int(col.g * light);
            int b = int(col.b * light);

            for (int y = wallTop; y <= wallBottom; y++) {
                gotoxy(x + 1, y + 1);
                setBackground(r, g, b);
                cout << ' ';
            }
        }
        resetColor();

        // 3. Спрайты (объекты)
        sort(objects.begin(), objects.end(),
             [&](Object* a, Object* b) {
                 float da = (a->x - player.x)*(a->x - player.x) +
                            (a->y - player.y)*(a->y - player.y);
                 float db = (b->x - player.x)*(b->x - player.x) +
                            (b->y - player.y)*(b->y - player.y);
                 return da > db;   // дальние — первыми
             });

        for (auto obj : objects) {
            if (!obj->active) continue;
            float dx = obj->x - player.x;
            float dy = obj->y - player.y;
            float dist = sqrt(dx*dx + dy*dy);

            float spriteAngle = atan2(dy, dx) - player.angle;
            while (spriteAngle >  PI) spriteAngle -= 2.0f * PI;
            while (spriteAngle < -PI) spriteAngle += 2.0f * PI;

            if (fabs(spriteAngle) > FOV/2.0f + 0.2f) continue;

            float screenX = (SCREEN_WIDTH / 2.0f) *
                            (1.0f + tan(spriteAngle) / tan(FOV/2.0f));
            int spriteScreenX = int(screenX);
            if (spriteScreenX < 0 || spriteScreenX >= SCREEN_WIDTH) continue;

            float invDist = 1.0f / dist;
            float bottomY = SCREEN_HEIGHT/2.0f -
                            (EYE_HEIGHT - obj->z) * invDist * focalLen;
            float topY    = SCREEN_HEIGHT/2.0f -
                            (EYE_HEIGHT - (obj->z + 1.0f)) * invDist * focalLen;
            int drawStartY = max(0, (int)(topY));
            int drawEndY   = min(SCREEN_HEIGHT - 1, (int)(bottomY));

            float light = lightFactorWall(dist);
            int r = int(obj->color.r * light);
            int g = int(obj->color.g * light);
            int b = int(obj->color.b * light);

            for (int y = drawStartY; y <= drawEndY; y++) {
                if (dist < zBuffer[spriteScreenX]) {
                    gotoxy(spriteScreenX + 1, y + 1);
                    setBackground(r, g, b);
                    setForeground(0, 0, 0);
                    cout << obj->spriteChar;
                }
            }
        }
        resetColor();

        // 4. Ввод команды
        gotoxy(1, SCREEN_HEIGHT + 1);
        cout << "Command (w/a/s/d/q/e/space/x): ";
        char cmd;
        cin >> cmd;

        // 5. Обработка движения игрока
        float moveSpeed = PLAYER_SPEED * dt;
        float rotSpeed  = PLAYER_ROT_SPEED * dt;
        float moveX = 0.0f, moveY = 0.0f;
        switch (cmd) {
            case 'w': moveX =  cos(player.angle) * moveSpeed;
                      moveY =  sin(player.angle) * moveSpeed; break;
            case 's': moveX = -cos(player.angle) * moveSpeed;
                      moveY = -sin(player.angle) * moveSpeed; break;
            case 'a': moveX =  cos(player.angle - PI/2.0f) * moveSpeed;
                      moveY =  sin(player.angle - PI/2.0f) * moveSpeed; break;
            case 'd': moveX =  cos(player.angle + PI/2.0f) * moveSpeed;
                      moveY =  sin(player.angle + PI/2.0f) * moveSpeed; break;
            case 'q': player.angle -= rotSpeed; break;
            case 'e': player.angle += rotSpeed; break;
            case ' ': {
                Projectile* proj = new Projectile(player.x, player.y,
                                                  player.z + 0.5f, player.angle);
                objects.push_back(proj);
                break;
            }
            case 'x': running = false; break;
        }

        // коллизия игрока со стенами (покадровое смещение)
        float newX = player.x + moveX;
        float newY = player.y + moveY;
        if (!map.isWall(int(newX), int(player.y))) player.x = newX;
        if (!map.isWall(int(player.x), int(newY))) player.y = newY;

        // 6. Обновление объектов
        for (auto obj : objects) {
            if (!obj->active) continue;
            // сохраняем старые координаты на случай отката
            float oldX = obj->x, oldY = obj->y;
            obj->Update(dt);

            // простая коллизия со стенами – если попали в стену, возвращаем объект
            if (map.isWall(int(obj->x), int(obj->y))) {
                obj->x = oldX;
                obj->y = oldY;
                // для снарядов – деактивируем при касании стены
                if (dynamic_cast<Projectile*>(obj)) {
                    obj->active = false;
                }
            }

            // удаляем объекты, улетевшие далеко или с нулевым здоровьем
            if (obj->health <= 0) obj->active = false;
        }

        // удаляем неактивные объекты
        objects.erase(
            remove_if(objects.begin(), objects.end(),
                      [](Object* o) { return !o->active; }),
            objects.end());
    }

    // очистка памяти
    for (auto o : objects) delete o;
    return 0;
}