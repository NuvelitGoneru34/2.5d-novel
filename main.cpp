#include "raylib.h"
#include "player.h"
#include "map.h"
#include "furniture.h"

int main() {
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Zarmas");
    //ToggleFullscreen();
    SetTargetFPS(120);

    //комната героя
    Furniture writing_desk = { 0, 0.8, 2.0, 3.2, 2.0, 0, 0, true, false, 0 };
    furniture_list[0] = writing_desk;
    Furniture flower = { 1, 0.6, 0.6, 3.2, 1.2 , 0, 0, true, false, 0 };
    furniture_list[1] = flower;
    Furniture bedside_table = { 2, 0.9, 0.8, 2.05, 1.0, 0, 0, true, false, 0 };
    furniture_list[2] = bedside_table;
    Furniture bed = { 3, 0.9, 2.0, 1.0, 1.0, 0, 0, true, false, 0 };
    furniture_list[3] = bed;
    Furniture wardrobe = { 4, 0.8, 1.9, 1.0, 3.1, 0, 0, true, false, 0 };
    furniture_list[4] = wardrobe;

    //жилая комната 1
    Furniture basketball_hoop = { 5, 0.6, 0.6, 13.0, 2.2, 0, 0, false, false, 0 };
    furniture_list[5] = basketball_hoop;
    Furniture flower1 = { 6, 0.6, 0.6, 13.2, 1.2 , 0, 0, true, false, 0 };
    furniture_list[6] = flower1;
    Furniture bedside_table1 = { 7, 0.9, 0.8, 14.05, 4.2, 0, 0, true, false, 0 };
    furniture_list[7] = bedside_table1;
    Furniture bed1 = { 8, 0.9, 2.0, 13.0, 3.0, 0, 0, true, false, 0 };
    furniture_list[8] = bed1;
    Furniture wardrobe1 = { 9, 2.0, 0.8, 14.0, 1.0, 0, 0, true, false, 0 };
    furniture_list[9] = wardrobe1;

    //жилая комната 2
    Furniture workbench = { 10, 2.0, 0.8, 32.0, 9.0, 0, 0, true, false, 0 };
    furniture_list[10] = workbench;
    Furniture flower2 = { 11, 0.6, 0.6, 34.2, 9.2 , 0, 0, true, false, 0 };
    furniture_list[11] = flower2;
    Furniture bedside_table2 = { 12, 0.8, 0.9, 34.2, 10.05, 0, 0, true, false, 0 };
    furniture_list[12] = bedside_table2;
    Furniture bed2 = { 13, 2.0, 0.9, 33.0, 11.1, 0, 0, true, false, 0 };
    furniture_list[13] = bed2;
    Furniture wardrobe2 = { 14, 2.0, 0.8, 31.0, 11.2, 0, 0, true, false, 0 };
    furniture_list[14] = wardrobe2;

    //техническое помещение
    Furniture shelf = { 15, 0.8, 2.0, 17.0, 1.0, 0, 0, true, false, 0 };
    furniture_list[15] = shelf;
    Furniture shelf1 = { 16, 0.8, 2.0, 17.0, 3.0, 0, 0, true, false, 0 };
    furniture_list[16] = shelf1;
    Furniture box = { 17, 0.9, 0.9, 18.1, 1.1, 0, 0, true, false, 0 };
    furniture_list[17] = box;

    //склад
    Furniture shelf2 = { 18, 2.0, 0.8, 31.0, 13.0, 0, 0, true, false, 0 };
    furniture_list[18] = shelf2;
    Furniture shelf3 = { 19, 2.0, 0.8, 33.0, 13.0, 0, 0, true, false, 0 };
    furniture_list[19] = shelf3;
    Furniture shelf4 = { 20, 0.8, 2.0, 34.2, 14.0, 0, 0, true, false, 0 };
    furniture_list[20] = shelf4;
    Furniture shelf5 = { 21, 0.8, 2.0, 34.2, 16.0, 0, 0, true, false, 0 };
    furniture_list[21] = shelf5;
    Furniture shelf6 = { 22, 0.8, 2.0, 34.2, 18.0, 0, 0, true, false, 0 };
    furniture_list[22] = shelf6;
    Furniture double_shelf = { 23, 1.9, 1.8, 31.0, 15.1, 0, 0, true, false, 0 };
    furniture_list[23] = double_shelf;
    Furniture writing_desk1 = { 24, 2.0, 0.8, 31.0, 19.0, 0, 0, true, false, 0 };
    furniture_list[24] = writing_desk1;

    //библиотека
    Furniture writing_desk2 = { 25, 2.0, 0.8, 20.0, 24.2, 0, 0, true, false, 0 };
    furniture_list[25] = writing_desk2;
    Furniture flower3 = { 26, 0.6, 0.6, 23.2, 30.2, 0, 0, true, false, 0 };
    furniture_list[26] = flower3;
    Furniture bookcase = { 27, 2.0, 0.8, 21.0, 30.2, 0, 0, true, false, 0 };
    furniture_list[27] = bookcase;
    Furniture bookcase1 = { 28, 2.0, 0.8, 24.0, 30.2, 0, 0, true, false, 0 };
    furniture_list[28] = bookcase1;
    Furniture bookcase2 = { 29, 0.8, 2.0, 20.0, 28.0, 0, 0, true, false, 0 };
    furniture_list[29] = bookcase2;
    Furniture bookcase3 = { 30, 0.8, 2.0, 26.2, 28.0, 0, 0, true, false, 0 };
    furniture_list[30] = bookcase3;
    Furniture bookcase4 = { 31, 0.8, 2.0, 26.2, 24.0, 0, 0, true, false, 0 };
    furniture_list[31] = bookcase4;
    Furniture bookcase_long = { 32, 3.0, 0.8, 23.0, 23.0, 0, 0, true, false, 0 };
    furniture_list[32] = bookcase_long;
    Furniture bookcase_long1 = { 33, 3.0, 0.8, 22.0, 26.1, 0, 0, true, false, 0 };
    furniture_list[33] = bookcase_long1;
    Furniture bookcase_long2 = { 34, 3.0, 0.8, 22.0, 28.1, 0, 0, true, false, 0 };
    furniture_list[34] = bookcase_long2;

    //читальный зал
    Furniture table = { 35, 0.8, 2.0, 28.0, 28.0, 0, 0, true, false, 0 };
    furniture_list[35] = table;
    Furniture table1 = { 36, 0.8, 2.0, 30.1, 25.0, 0, 0, true, false, 0 };
    furniture_list[36] = table1;
    Furniture table_long = { 37, 0.8, 3.0, 30.1, 28.0, 0, 0, true, false, 0 };
    furniture_list[37] = table_long;
    Furniture flower4 = { 38, 0.6, 0.6, 28.2, 30.2 , 0, 0, true, false, 0 };
    furniture_list[38] = flower4;

    //медблок
    Furniture writing_desk3 = { 39, 0.8, 2.0, 2.2, 15.0, 0, 0, true, false, 0 };
    furniture_list[39] = writing_desk3;
    Furniture medical_locker = { 40, 2.0, 0.8, 1.0, 13.0, 0, 0, true, false, 0 };
    furniture_list[40] = medical_locker;
    Furniture medical_locker1 = { 41, 2.0, 0.8, 3.0, 13.0, 0, 0, true, false, 0 };
    furniture_list[41] = medical_locker1;

    furniture_count = 42;

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
                        color = { (unsigned char)(139 + 0), (unsigned char)(69 + 0), (unsigned char)(19 + 0), 255 };
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

        for (int i = 0; i < furniture_count; i++) {
            Furniture* f = &furniture_list[i];
            Color color = f->is_interactable ? BLUE : DARKGREEN;
            DrawRectangle(f->x * size, f->y * size, f->width * size, f->height * size, color);
        }

        DrawCircle(player.x * size, player.y * size, 5, RED);
        DrawLine(player.x * size, player.y * size,
            (player.x + cosf(player.angle) * 2) * size,
            (player.y + sinf(player.angle) * 2) * size, RED);
        EndDrawing();
    }
    CloseWindow();
}