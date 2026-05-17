#include "raylib.h"
#include "player.h"
#include "map.h"

int main() {
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Game");
    SetTargetFPS(120);

    Player player = { 5, 5, 0, 0.015f, 0.25f, 16 };
    Mouse mouse = { true, 0.003f };
    DisableCursor();

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(BLACK);

        update_mouse(&player, mouse.sensitivity, SCREEN_WIDTH, SCREEN_HEIGHT);
        float  real_x = 0, real_y = 0;
        control_walking(player.angle, player.speed, &real_x, &real_y);
        move_player(&player, real_x, real_y, map);

        int size = 80;
        for (int y = 0; y < 10; y++) {
            for (int x = 0; x < 10; x++) {
                Color color = (map[y][x] == 1) ? DARKGRAY : LIGHTGRAY;
                DrawRectangle(x * size, y * size, size, size, color);
            }
        }
        DrawCircle(player.x * size, player.y * size, 5, RED);
        DrawLine(player.x * size, player.y * size,
            (player.x + cosf(player.angle) * 2) * size,
            (player.y + sinf(player.angle) * 2) * size, RED);
        EndDrawing();
    }
    CloseWindow();
}