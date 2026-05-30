#include "raylib.h"
#include "player.h"
#include "map.h"
#include "furniture.h"
#include "raycast.h"

int main() {
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Zarmas");
    ToggleFullscreen();
    SetWindowState(FLAG_VSYNC_HINT);
    SetTargetFPS(60);
    InitTextures();
    PrepareTextures();
    InitAllFurniture();

    Player player = { 2.5, 3.5, 0, 0.03f, 0.03f,0, 2.0f, 0.15f, 32 , PI / 3 , PI / 3};
    Mouse mouse = { true, 0.003f };
    DisableCursor();

    while (!WindowShouldClose()) {

        if (IsKeyPressed(KEY_F11)) ToggleFullscreen();
        if (IsKeyPressed(KEY_V)) {
            if (IsWindowState(FLAG_VSYNC_HINT)) {
                ClearWindowState(FLAG_VSYNC_HINT);
                SetTargetFPS(60);
            }
            else {
                SetWindowState(FLAG_VSYNC_HINT);
                SetTargetFPS(60);
            }
        }

        update_mouse(&player, mouse.sensitivity, SCREEN_WIDTH, SCREEN_HEIGHT);
        float  real_x = 0, real_y = 0;
        control_player(&player, &real_x, &real_y, map, doors);
        move_player(&player, real_x, real_y, map);
        UpdateDoors(doors);
        raycast(&player);
    }
    CloseWindow();
}