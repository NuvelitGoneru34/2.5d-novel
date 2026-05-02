#pragma once
#include "raylib.h"
#include <vector>

static Font _safeFont = { 0 };

bool LoadSafeFont(const char* fontPath, int fontSize = 32) {
    std::vector<int> codepoints;

    for (int i = 32; i <= 126; ++i)
        codepoints.push_back(i);

    for (int i = 1024; i <= 1279; ++i)
        codepoints.push_back(i);

    Font font = LoadFontEx(fontPath, fontSize, codepoints.data(), (int)codepoints.size());
    if (font.texture.id == 0) {
        TraceLog(LOG_ERROR, "SafeFont: не удалось загрузить '%s'", fontPath);
        return false;
    }

    if (_safeFont.texture.id != 0)
        UnloadFont(_safeFont);

    _safeFont = font;
    return true;
}

void UnloadSafeFont() {
    if (_safeFont.texture.id != 0) {
        UnloadFont(_safeFont);
        _safeFont = { 0 };
    }
}

void DrawSafeText(const char* text, int x, int y, int fontSize, Color color) {
    if (_safeFont.texture.id == 0) {
        DrawText(text, x, y, fontSize, color);
        return;
    }
    DrawTextEx(_safeFont, text, { (float)x, (float)y }, (float)fontSize, 1.0f, color);
}

Font* GetSafeFont() {
    return &_safeFont;
}