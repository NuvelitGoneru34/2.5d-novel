#include "player.h"
#include "map.h"
#include "furniture.h"

void control_player(Player* player, float* real_x, float* real_y, Cell map[MAP_HEIGHT][MAP_WIDTH], DoorState doors[MAP_HEIGHT][MAP_WIDTH]) {
    float dx = 0, dy = 0;
    bool is_walk = false;

    if (IsKeyDown(KEY_W) || IsKeyDown(KEY_UP)) {
        dx += cosf(player->angle);
        dy += sinf(player->angle);
        is_walk = true;
    }
    if (IsKeyDown(KEY_S) || IsKeyDown(KEY_DOWN)) {
        dx -= cosf(player->angle);
        dy -= sinf(player->angle);
        is_walk = true;
    }
    if (IsKeyDown(KEY_A) || IsKeyDown(KEY_LEFT)) {
        dx += cosf(player->angle - PI / 2);
        dy += sinf(player->angle - PI / 2);
        is_walk = true;
    }
    if (IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT)) {
        dx += cosf(player->angle + PI / 2);
        dy += sinf(player->angle + PI / 2);
        is_walk = true;
    }
    float desired_speed = player->base_speed;
    float desired_fov = player->actually_fov;
    if ((IsKeyDown(KEY_LEFT_SHIFT) || IsKeyDown(KEY_RIGHT_SHIFT)) && is_walk) {
        desired_speed *= player->acceleration;
        desired_fov *= 1.05f;
        player->is_running = true;
    }
    else {
        player->is_running = false;
    }

    float smoothing = 1.0f - expf(-20.0f * GetFrameTime());
    player->speed += (desired_speed - player->speed) * smoothing;
    player->fov += (desired_fov - player->fov) * smoothing;

    if (IsKeyPressed(KEY_E) || IsKeyPressed(KEY_ENTER)) {
        interact(player, map, doors);
    }

    float actualy_speed = sqrtf(dx * dx + dy * dy);
    if (actualy_speed > 1.0f) {
        dx /= actualy_speed;
        dy /= actualy_speed;
    }

    *real_x = dx * player->speed;
    *real_y = dy * player->speed;
}

void move_player(Player* player, float dx, float dy, Cell map[MAP_HEIGHT][MAP_WIDTH]) {
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
            if (IsKeyDown(KEY_SPACE)) {
                pushX += newX - px;
                pushY += newY - py;
                continue;
            }
            blocked++;
            pushX += newX - px;
            pushY += newY - py;
        }
    }

    if (blocked > 0) {
        float len = sqrtf(pushX * pushX + pushY * pushY);
        if (len > 0.0001f) {
            pushX /= len;
            pushY /= len;
        }
        float push_strength = ((float)blocked / player->num_points) * player->radius * 0.35f;
        if (player->is_running) {
            push_strength *= player->acceleration;
        }
        player->x = newX + pushX * push_strength;
        player->y = newY + pushY * push_strength;
    }
    else {
        player->x = newX;
        player->y = newY;
    }
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

    DoorState* door = &doors[ty][tx];
    if (map[ty][tx].type == CELL_LOCKED_DOOR) return;
    if (!door->is_opening) {
        door->is_opening = true;
        if (door->is_open) {
            door->dir = -1.0f;
        }
        else {
            door->dir = 1.0f;
        }
    }

    float ix = player->x + cosf(player->angle);
    float iy = player->y + sinf(player->angle);
    Furniture* furniture = GetFAtPoint(ix, iy);
    if (furniture != NULL && furniture->is_interactable) {
        furniture->interacted = !furniture->interacted;
    }
}