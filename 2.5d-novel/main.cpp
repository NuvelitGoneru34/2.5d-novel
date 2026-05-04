#include "raylib.h"
#include "font_choise.h"

int main() {
    InitWindow(1000, 800, "Minimal font");

    Font font = LoadSomeFont(255);

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(BLACK);
        if (font.texture.id != 0)
            DrawTextEx(font, "Привет мир!", {360, 370}, 32, 1, Color{255, 255, 255, 255});
        else
            DrawText("Font error", 10, 10, 20, RED);
        EndDrawing();
    }
    UnloadFont(font);
    CloseWindow();
}