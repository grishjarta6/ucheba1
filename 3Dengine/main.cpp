#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include <algorithm>
#include <thread>
#include <chrono>
#include <atomic>

using namespace std;

// ---------- настройки движка ----------
const int SCREEN_WIDTH  = 80;
const int SCREEN_HEIGHT = 24;
const double LIGHT_RADIUS = 8.0;           // радиус фонарика (клетки)
const double GRAVITY      = 0.002;         // ускорение свободного падения
const double FRAME_DT     = 1.0;           // шаг времени
const double MOVE_SPEED   = 0.05;          // линейная скорость игрока
const double ROT_SPEED    = 0.03;          // угловая скорость игрока

// ---------- ANSI-управление ----------
string colorCode(int index) { return "\033[38;5;" + to_string(index) + "m"; }
string resetColor()       { return "\033[0m"; }
string hideCursor()       { return "\033[?25l"; }
string showCursor()       { return "\033[?25h"; }
string clearScreen()      { return "\033[2J\033[H"; }

// градиент яркости
char brightnessChar(double brightness) {
    static const string grad = " .:-=+*#%@";
    if (brightness <= 0.0) return ' ';
    if (brightness >= 1.0) return '@';
    int idx = (int)(brightness * (grad.size() - 1));
    return grad[idx];
}

// ---------- карта ----------
vector<string> mapGrid;
int mapWidth = 0, mapHeight = 0;

bool isWall(int x, int y) {
    if (x < 0 || x >= mapWidth || y < 0 || y >= mapHeight) return true;
    return mapGrid[y][x] == '#' || mapGrid[y][x] == 'D';
}

// ---------- игрок ----------
struct Player {
    double posX, posY;
    double dirX, dirY;
    double planeX, planeY;
};

// ---------- текстуры (спрайты объектов) ----------
struct Texture {
    vector<string> data;       // строки текстуры
    int width, height;
    Texture(const vector<string>& d) : data(d) {
        height = (int)data.size();
        width = 0;
        for (auto& row : data)
            if ((int)row.size() > width) width = (int)row.size();
    }
};

// предопределённые текстуры
Texture texCube({
    "  ####  ",
    " ###### ",
    "########",
    "########",
    " ###### ",
    "  ####  "
});

Texture texSphere({
    "   OO   ",
    " OOOOOO ",
    "OOOOOOOO",
    "OOOOOOOO",
    " OOOOOO ",
    "   OO   "
});

// ---------- буфер экрана ----------
struct ScreenBuffer {
    char   chars[SCREEN_HEIGHT][SCREEN_WIDTH];
    int    colors[SCREEN_HEIGHT][SCREEN_WIDTH];
    double zBuffer[SCREEN_WIDTH];

    ScreenBuffer() {
        for (int y = 0; y < SCREEN_HEIGHT; ++y)
            for (int x = 0; x < SCREEN_WIDTH; ++x) {
                chars[y][x] = ' ';
                colors[y][x] = 0;
            }
        for (int x = 0; x < SCREEN_WIDTH; ++x) zBuffer[x] = 1e30;
    }
};

// ---------- базовый объект ----------
class Object {
public:
    double x, y, z;          // позиция (z – высота над полом)
    double vx, vy, vz;       // скорость
    double health;
    char   glyph;            // символ по умолчанию (если нет текстуры)
    int    color;            // индекс ANSI 256
    bool   alive;
    Texture* texture;        // если не nullptr – объект текстурирован

    Object(double px, double py, double pz, char g, int col, Texture* tex = nullptr)
        : x(px), y(py), z(pz), vx(0), vy(0), vz(0), health(1), glyph(g), color(col), alive(true), texture(tex) {}

    virtual void update(float dt, class Game* game) {}
    virtual void onCollide(Object* other) {}

    void applyPhysics(float dt, Game* game);
    void moveX(float dt, Game* game);
    void moveY(float dt, Game* game);
};

class Game {
public:
    Player player;
    vector<Object*> objects;
    ScreenBuffer screen;

    Game() {
        // камера: центр комнаты, смотрит вправо
        player.posX = 7.5;
        player.posY = 5.5;
        player.dirX = 1.0;
        player.dirY = 0.0;
        player.planeX = 0.0;
        player.planeY = 0.66;
    }

    void loadMap(const vector<string>& data) {
        mapGrid = data;
        mapWidth  = (int)mapGrid[0].size();
        mapHeight = (int)mapGrid.size();
    }

    void update(float dt) {
        for (auto obj : objects)
            if (obj->alive) obj->update(dt, this);

        // столкновения между объектами
        for (size_t i = 0; i < objects.size(); ++i) {
            if (!objects[i]->alive) continue;
            for (size_t j = i + 1; j < objects.size(); ++j) {
                if (!objects[j]->alive) continue;
                double dx = objects[i]->x - objects[j]->x;
                double dy = objects[i]->y - objects[j]->y;
                if (sqrt(dx*dx + dy*dy) < 0.5) {
                    objects[i]->onCollide(objects[j]);
                    objects[j]->onCollide(objects[i]);
                }
            }
        }
        objects.erase(remove_if(objects.begin(), objects.end(),
            [](Object* o) { if (!o->alive) { delete o; return true; } return false; }),
            objects.end());
    }

    void render() {
        screen = ScreenBuffer();
        renderWalls();
        renderFloorCeiling();
        renderSprites();
        drawScreen();
    }

    void moveForward(double amount) {
        double newX = player.posX + player.dirX * amount;
        double newY = player.posY + player.dirY * amount;
        if (!isWall((int)newX, (int)newY)) {
            player.posX = newX;
            player.posY = newY;
        }
    }
    void moveSide(double amount) {
        double newX = player.posX + player.planeX * amount;
        double newY = player.posY + player.planeY * amount;
        if (!isWall((int)newX, (int)newY)) {
            player.posX = newX;
            player.posY = newY;
        }
    }
    void rotate(double angle) {
        double oldDirX = player.dirX;
        player.dirX = player.dirX * cos(angle) - player.dirY * sin(angle);
        player.dirY = oldDirX * sin(angle) + player.dirY * cos(angle);
        double oldPlaneX = player.planeX;
        player.planeX = player.planeX * cos(angle) - player.planeY * sin(angle);
        player.planeY = oldPlaneX * sin(angle) + player.planeY * cos(angle);
    }

private:
    void renderWalls();
    void renderFloorCeiling();
    void renderSprites();
    void drawScreen();
};

// ---------- физика объекта ----------
void Object::applyPhysics(float dt, Game* game) {
    vz -= GRAVITY * dt;
    z += vz * dt;
    if (z < 0.0) { z = 0.0; vz = 0.0; }
    moveX(dt, game);
    moveY(dt, game);
}
void Object::moveX(float dt, Game* game) {
    double newX = x + vx * dt;
    if (!isWall((int)newX, (int)y)) x = newX; else vx = 0.0;
}
void Object::moveY(float dt, Game* game) {
    double newY = y + vy * dt;
    if (!isWall((int)x, (int)newY)) y = newY; else vy = 0.0;
}

// ---------- конкретные объекты ----------
class Cube : public Object {
public:
    Cube(double px, double py, double pz) : Object(px, py, pz, 'C', 160, &texCube) {}
    void update(float dt, Game* game) override { applyPhysics(dt, game); }
};

class Sphere : public Object {
public:
    Sphere(double px, double py, double pz) : Object(px, py, pz, 'O', 226, &texSphere) {}
    void update(float dt, Game* game) override { applyPhysics(dt, game); }
};

// ---------- рендер стен ----------
void Game::renderWalls() {
    for (int x = 0; x < SCREEN_WIDTH; ++x) {
        double cameraX = 2.0 * x / (double)SCREEN_WIDTH - 1.0;
        double rayDirX = player.dirX + player.planeX * cameraX;
        double rayDirY = player.dirY + player.planeY * cameraX;

        int mapX = (int)player.posX, mapY = (int)player.posY;
        double deltaDistX = (rayDirX == 0) ? 1e30 : abs(1.0 / rayDirX);
        double deltaDistY = (rayDirY == 0) ? 1e30 : abs(1.0 / rayDirY);

        int stepX, stepY;
        double sideDistX, sideDistY;
        if (rayDirX < 0) { stepX = -1; sideDistX = (player.posX - mapX) * deltaDistX; }
        else            { stepX = 1;  sideDistX = (mapX + 1.0 - player.posX) * deltaDistX; }
        if (rayDirY < 0) { stepY = -1; sideDistY = (player.posY - mapY) * deltaDistY; }
        else            { stepY = 1;  sideDistY = (mapY + 1.0 - player.posY) * deltaDistY; }

        int side = 0;
        bool hit = false;
        while (!hit) {
            if (sideDistX < sideDistY) {
                sideDistX += deltaDistX; mapX += stepX; side = 0;
            } else {
                sideDistY += deltaDistY; mapY += stepY; side = 1;
            }
            if (isWall(mapX, mapY)) hit = true;
        }

        double perpDist = (side == 0) ? (sideDistX - deltaDistX) : (sideDistY - deltaDistY);
        screen.zBuffer[x] = perpDist;

        int lineHeight = (int)(SCREEN_HEIGHT / perpDist);
        int drawStart = -lineHeight / 2 + SCREEN_HEIGHT / 2;
        if (drawStart < 0) drawStart = 0;
        int drawEnd = lineHeight / 2 + SCREEN_HEIGHT / 2;
        if (drawEnd >= SCREEN_HEIGHT) drawEnd = SCREEN_HEIGHT - 1;

        double brightness = 1.0 - min(1.0, perpDist / LIGHT_RADIUS);
        if (brightness < 0.0) brightness = 0.0;
        int grayVal = (int)(brightness * 255.0);
        int colorIdx = 232 + (grayVal * 24) / 256;

        // разные символы для осей X и Y
        char wallChar;
        if (side == 0) wallChar = '|';   // стена по X
        else           wallChar = '#';   // стена по Y
        // яркостный символ накладываем поверх, чтобы сохранить глубину
        char brightSym = brightnessChar(brightness);
        if (brightSym != ' ') wallChar = brightSym;

        for (int y = drawStart; y <= drawEnd; ++y) {
            screen.chars[y][x] = wallChar;
            screen.colors[y][x] = colorIdx;
        }
    }
}

// ---------- пол и потолок ----------
void Game::renderFloorCeiling() {
    double posX = player.posX, posY = player.posY;
    double dirX = player.dirX, dirY = player.dirY;
    double planeX = player.planeX, planeY = player.planeY;

    for (int y = 0; y < SCREEN_HEIGHT; ++y) {
        bool isFloor = (y > SCREEN_HEIGHT / 2);
        double rowDistance = (double)SCREEN_HEIGHT / (2.0 * y - SCREEN_HEIGHT);
        if (!isFloor) rowDistance = -rowDistance;

        double stepX = rowDistance * (planeX * 2) / SCREEN_WIDTH;
        double stepY = rowDistance * (planeY * 2) / SCREEN_WIDTH;
        double floorX = posX + rowDistance * dirX;
        double floorY = posY + rowDistance * dirY;

        for (int x = 0; x < SCREEN_WIDTH; ++x) {
            int cellX = (int)floorX, cellY = (int)floorY;
            if (isWall(cellX, cellY)) continue;
            if (screen.chars[y][x] != ' ') continue;

            double dist = sqrt(pow(floorX - posX, 2) + pow(floorY - posY, 2));
            double brightness = 1.0 - min(1.0, dist / LIGHT_RADIUS);
            if (brightness < 0.0) brightness = 0.0;

            char c = isFloor ? brightnessChar(brightness * 0.6) : ' ';
            int colorIdx = isFloor ? (232 + (int)(brightness * 24 / 256)) : 0;

            screen.chars[y][x] = c;
            screen.colors[y][x] = colorIdx;

            floorX += stepX;
            floorY += stepY;
        }
    }
}

// ---------- рендер спрайтов с текстурами ----------
void Game::renderSprites() {
    // сбор и сортировка по расстоянию
    vector<pair<double, Object*>> sprites;
    for (auto obj : objects) {
        if (!obj->alive) continue;
        double dx = obj->x - player.posX;
        double dy = obj->y - player.posY;
        sprites.push_back({dx*dx + dy*dy, obj});
    }
    sort(sprites.begin(), sprites.end(),
        [](const auto& a, const auto& b) { return a.first > b.first; });

    double invDet = 1.0 / (player.planeX * player.dirY - player.dirX * player.planeY);

    for (auto& [_, obj] : sprites) {
        double spriteX = obj->x - player.posX;
        double spriteY = obj->y - player.posY;
        double transformX = invDet * (player.dirY * spriteX - player.dirX * spriteY);
        double transformY = invDet * (-player.planeY * spriteX + player.planeX * spriteY);
        if (transformY <= 0.0) continue;

        int spriteScreenX = (int)((SCREEN_WIDTH / 2.0) * (1.0 + transformX / transformY));
        // размер спрайта на экране (пропорционально расстоянию)
        int spriteHeight = abs((int)(SCREEN_HEIGHT / transformY));
        int spriteWidth  = spriteHeight;   // квадратный спрайт

        int drawStartY = -spriteHeight / 2 + SCREEN_HEIGHT / 2 + (int)(obj->z * SCREEN_HEIGHT / transformY);
        int drawEndY   =  spriteHeight / 2 + SCREEN_HEIGHT / 2 + (int)(obj->z * SCREEN_HEIGHT / transformY);
        int drawStartX = -spriteWidth / 2 + spriteScreenX;
        int drawEndX   =  spriteWidth / 2 + spriteScreenX;

        // освещение: затухание с расстоянием
        double brightness = 1.0 - min(1.0, transformY / LIGHT_RADIUS);
        if (brightness < 0.0) brightness = 0.0;
        int colorIdx = obj->color;

        if (obj->texture != nullptr) {
            // текстурированный спрайт
            Texture& tex = *obj->texture;
            for (int stripe = drawStartX; stripe < drawEndX; ++stripe) {
                if (stripe < 0 || stripe >= SCREEN_WIDTH) continue;
                if (transformY > screen.zBuffer[stripe]) continue;

                // координата текстуры по X
                double texX = (double)(stripe - drawStartX) / spriteWidth;
                int texCol = min((int)(texX * tex.width), tex.width - 1);

                for (int y = drawStartY; y < drawEndY; ++y) {
                    if (y < 0 || y >= SCREEN_HEIGHT) continue;
                    if (screen.chars[y][stripe] != ' ') continue; // не затираем стены

                    double texY = (double)(y - drawStartY) / spriteHeight;
                    int texRow = min((int)(texY * tex.height), tex.height - 1);

                    char c = tex.data[texRow][texCol];
                    if (c != ' ') {
                        // уменьшаем яркость символа в зависимости от освещения
                        char brightSym = brightnessChar(brightness);
                        // если текстура не прозрачная, заменяем на символ с учётом яркости
                        if (brightSym != ' ') c = brightSym;
                        screen.chars[y][stripe] = c;
                        screen.colors[y][stripe] = colorIdx;
                    }
                }
            }
        } else {
            // обычный спрайт (один символ)
            for (int stripe = drawStartX; stripe < drawEndX; ++stripe) {
                if (stripe < 0 || stripe >= SCREEN_WIDTH) continue;
                if (transformY > screen.zBuffer[stripe]) continue;
                for (int y = drawStartY; y < drawEndY; ++y) {
                    if (y < 0 || y >= SCREEN_HEIGHT) continue;
                    screen.chars[y][stripe] = obj->glyph;
                    screen.colors[y][stripe] = colorIdx;
                }
            }
        }
    }
}

// ---------- вывод кадра ----------
void Game::drawScreen() {
    cout << clearScreen() << hideCursor();
    string output;
    for (int y = 0; y < SCREEN_HEIGHT; ++y) {
        for (int x = 0; x < SCREEN_WIDTH; ++x) {
            output += colorCode(screen.colors[y][x]);
            output += screen.chars[y][x];
        }
        output += resetColor() + "\n";
    }
    cout << output << flush;
    cout << showCursor();
}

// ---------- поток ввода (построчный с Enter) ----------
atomic<char> inputCmd{0};

void inputThreadFunc() {
    string line;
    while (getline(cin, line)) {
        if (!line.empty()) inputCmd.store(line[0]);
    }
}

// ---------- главный цикл ----------
int main() {
    // пустая комната
    vector<string> level = {
        "################",
        "#              #",
        "#              #",
        "#              #",
        "#              #",
        "#              #",
        "#              #",
        "#              #",
        "################"
    };

    Game game;
    game.loadMap(level);

    // куб и шар перед игроком
    game.objects.push_back(new Cube(8.5, 5.5, 0.0));
    game.objects.push_back(new Sphere(10.5, 5.5, 0.0));

    thread inpThread(inputThreadFunc);
    inpThread.detach();

    cout << "Управление: W/S – вперёд/назад, A/D – вбок, Q/E – поворот (нажимайте Enter после символа)" << endl;

    while (true) {
        char cmd = inputCmd.exchange(0);
        switch (cmd) {
            case 'w': game.moveForward( MOVE_SPEED); break;
            case 's': game.moveForward(-MOVE_SPEED); break;
            case 'a': game.moveSide(-MOVE_SPEED);    break;
            case 'd': game.moveSide( MOVE_SPEED);    break;
            case 'q': game.rotate(-ROT_SPEED);       break;
            case 'e': game.rotate( ROT_SPEED);       break;
            default: break;
        }

        game.update(FRAME_DT);
        game.render();
        this_thread::sleep_for(chrono::milliseconds(30));
    }

    return 0;
}