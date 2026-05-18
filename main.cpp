#include "raylib.h"
#include "player.h"
#include "map.h"

int main() {
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Zarmas");
    //ToggleFullscreen();
    SetTargetFPS(120);

    Player player = { 2.5, 3.5, 0, 0.015f, 0, 2.0f, 0.25f, 32 };
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
        control_player(&player, &real_x, &real_y, map, doors);
        move_player(&player, real_x, real_y, map);
        UpdateDoors(doors);

        int size = fmin(SCREEN_WIDTH / MAP_WIDTH, SCREEN_HEIGHT / MAP_HEIGHT);
        for (int y = 0; y < MAP_HEIGHT; y++) {
            for (int x = 0; x < MAP_WIDTH; x++) {
                Color color;
                switch (map[y][x].type) {
                case CELL_WALL: color = DARKGRAY; break;
                case CELL_DOOR: {
                    DoorState* d = &doors[y][x];
                    if (d->is_open && d->offset >= 1.0f) {
                        color = GREEN;
                    }
                    else if (d->is_opening) {
                        float t = d->offset;
                        color = { (unsigned char)(139 + (0 - 139) * t), (unsigned char)(69 + (255 - 69) * t), (unsigned char)(19 + (0 - 19) * t), 255 };
                    }
                    else {
                        color = BROWN;
                    }
                } break;
                case CELL_EMPTY:
                default: color = LIGHTGRAY; break;
                }
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