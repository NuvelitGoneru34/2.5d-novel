#include "player.h"
#include "map.h"
#include "furniture.h"

void control_player(Player *player, float *real_x, float *real_y, Cell map[MAP_HEIGHT][MAP_WIDTH], DoorState doors[MAP_HEIGHT][MAP_WIDTH]) {
    float dx = 0, dy = 0;

    if (IsKeyDown(KEY_W)) {
        dx += cosf(player->angle);
        dy += sinf(player->angle);
    }
    if (IsKeyDown(KEY_S)) {
        dx -= cosf(player->angle);
        dy -= sinf(player->angle);
    }
    if (IsKeyDown(KEY_A)) {
        dx += cosf(player->angle - PI / 2);
        dy += sinf(player->angle - PI / 2);
    }
    if (IsKeyDown(KEY_D)) {
        dx += cosf(player->angle + PI / 2);
        dy += sinf(player->angle + PI / 2);
    }
    float current_speed = player->speed;
    if (IsKeyDown(KEY_LEFT_SHIFT)) {
        current_speed *= player->acceleration;
        player->is_running = true;
    }
    else player->is_running = false;

    if (IsKeyDown(KEY_E)) {
        interact(player, map, doors);
    }

    float actualy_speed = sqrtf(dx * dx + dy * dy);
    if (actualy_speed > 1.0f) {
        dx /= actualy_speed;
        dy /= actualy_speed;
    }

    *real_x = dx * current_speed;
    *real_y = dy * current_speed;
}

void move_player(Player *player, float dx, float dy, Cell map[MAP_HEIGHT][MAP_WIDTH]) {
    float step = 2.0f * PI / player->num_points;

    float newX = player->x + dx;
    float newY = player->y + dy;

    int blocked = 0;
    float pushX = 0, pushY = 0;

    for (int i = 0; i < player->num_points; i++) {
        float angle = i * step;
        float px = newX + cosf(angle) * player->radius;
        float py = newY + sinf(angle) * player->radius;

        int cellX = (int)px;
        int cellY = (int)py;

        if (cellX < 0 || cellX >= MAP_WIDTH ||
            cellY < 0 || cellY >= MAP_HEIGHT ||
            IsSolid(map[cellY][cellX], &doors[cellY][cellX]) ||
            (GetFAtPoint(px, py) != NULL && GetFAtPoint(px, py)->is_solid)) {
            blocked++;
            pushX += newX - px;
            pushY += newY - py;
        }
    }

    float push_avoid_vector = sqrtf(pushX * pushX + pushY * pushY);
    if (push_avoid_vector > 0.0001f) {
        pushX /= push_avoid_vector;
        pushY /= push_avoid_vector;
    }

    float push_strength = ((float)blocked / player->num_points) * player->radius * 0.35f;
    if (player->is_running) {
        push_strength *= player->acceleration;
    }
    else push_strength = ((float)blocked / player->num_points) * player->radius * 0.35f;

    player->x = newX + pushX * push_strength;
    player->y = newY + pushY * push_strength;
}

void update_mouse(Player* player, float sensitivity, int screenWidth, int screenHeight) {
    Vector2 delta = GetMouseDelta();
    player->angle += delta.x * sensitivity;
    SetMousePosition(screenWidth / 2, screenHeight / 2);
}

void interact(Player* player, Cell map[MAP_HEIGHT][MAP_WIDTH], DoorState doors[MAP_HEIGHT][MAP_WIDTH]) {
    int tx = (int)(player->x + cosf(player->angle));
    int ty = (int)(player->y + sinf(player->angle));

    if (tx < 0 || tx >= MAP_WIDTH || ty < 0 || ty >= MAP_HEIGHT) return;

    if (map[ty][tx].type != CELL_DOOR) return;

    DoorState* door = &doors[ty][tx];

    if (!door->is_opening) {
        door->is_opening = true;
        if (door->is_open) {
            door->dir = -1.0f;
        }
        else {
            door->dir = 1.0f;
        }
    }
}