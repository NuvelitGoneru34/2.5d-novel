#ifndef RAYCAST_H
#define RAYCAST_H

#define MAX_TEXTURES 50

#include "raylib.h"
#include "map.h"
#include "player.h"

extern Texture2D Textures[MAX_TEXTURES];
extern float zBuffer[SCREEN_WIDTH];

void raycast(Player* player);
void InitTextures();
void PrepareTextures();

#endif
