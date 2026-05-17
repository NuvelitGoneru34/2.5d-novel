#ifndef FONT_CHOISE_H
#define FONT_CHOISE_H

#include "raylib.h"
#include <vector>

inline Font LoadSomeFont(unsigned char font_quality) {
    std::vector<int> codepoints;
    for (int i = 32; i <= 126; i++) codepoints.push_back(i);
    for (int i = 1024; i <= 1279; i++) codepoints.push_back(i);
    return LoadFontEx("minecraft_font.ttf", font_quality, codepoints.data(), codepoints.size());
}

#endif