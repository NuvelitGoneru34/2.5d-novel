#include "player.h"

void control_walking(float angle, float speed, float* real_x, float* real_y) {
    float dx = 0, dy = 0;

    if (IsKeyDown(KEY_W)) {
        dx += cosf(angle);
        dy += sinf(angle);
    }
    if (IsKeyDown(KEY_S)) {
        dx -= cosf(angle);
        dy -= sinf(angle);
    }
    if (IsKeyDown(KEY_A)) {
        dx += cosf(angle - PI / 2);
        dy += sinf(angle - PI / 2);
    }
    if (IsKeyDown(KEY_D)) {
        dx += cosf(angle + PI / 2);
        dy += sinf(angle + PI / 2);
    }

    float actualy_speed = sqrtf(dx * dx + dy * dy);
    if (actualy_speed > 1.0f) {
        dx /= actualy_speed;
        dy /= actualy_speed;
    }

    *real_x = dx * speed;
    *real_y = dy * speed;
}

void move_player(Player* player, float dx, float dy, int map[][10]) {
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

        if (cellX < 0 || cellX > 9 || cellY < 0 || cellY > 9 || map[cellY][cellX] == 1) {
            blocked++;
            pushX += newX - px;
            pushY += newY - py;
        }
    }

    if (blocked == 0) {
        player->x = newX;
        player->y = newY;
        return;
    }

    float push_avoid_vector = sqrtf(pushX * pushX + pushY * pushY);
    if (push_avoid_vector > 0.0001f) {
        pushX /= push_avoid_vector;
        pushY /= push_avoid_vector;
    }

    float push_strength = ((float)blocked / player->num_points) * player->radius * 0.35f;

    player->x = newX + pushX * push_strength;
    player->y = newY + pushY * push_strength;
}

void update_mouse(Player* player, float sensitivity, int screenWidth, int screenHeight) {
    Vector2 delta = GetMouseDelta();
    player->angle += delta.x * sensitivity;
    SetMousePosition(screenWidth / 2, screenHeight / 2);
}