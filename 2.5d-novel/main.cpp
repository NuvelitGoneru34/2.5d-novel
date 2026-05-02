#include "raylib.h"
#include "fonts_work.h"

int main() {
    InitWindow(800, 600, "Безопасный вывод текста");
    SetTargetFPS(60);

    if (!LoadSafeFont("C:/Windows/Fonts/arial.ttf", 36)) {
    }

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);

        DrawSafeText("Привет, мир! Hello, world!", 100, 100, 36, DARKGREEN);
        DrawSafeText("Размер шрифта можно менять", 100, 160, 24, DARKBLUE);
        DrawSafeText("Ёжик и ёлка - кириллица работает", 100, 220, 30, MAROON);

        DrawFPS(10, 10);
        EndDrawing();
    }

    UnloadSafeFont();
    CloseWindow();
    return 0;
}