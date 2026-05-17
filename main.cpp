#include "raylib.h"
#include "player.h"
#include "map.h"

int main() {
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Game");
    ToggleFullscreen();
    SetTargetFPS(120);

    Player player = { 5, 5, 0, 0.015f, 0, 0.25f, 16 };
    Mouse mouse = { true, 0.003f };
    DisableCursor();

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(BLACK);

        if (IsKeyPressed(KEY_F11)) {
            ToggleFullscreen();
        }

        update_mouse(&player, mouse.sensitivity, SCREEN_WIDTH, SCREEN_HEIGHT);
        float  real_x = 0, real_y = 0;
        control_walking(player.angle, player.speed, &player.is_running, &real_x, &real_y);
        move_player(&player, real_x, real_y, map);

        int size = SCREEN_WIDTH / MAP_WIDTH;
        for (int y = 0; y < MAP_HEIGHT; y++) {
            for (int x = 0; x < MAP_WIDTH; x++) {
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