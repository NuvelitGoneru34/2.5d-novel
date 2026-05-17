#ifndef PLAYER_H
#define PLAYER_H

#include "raylib.h"
#include <math.h>

typedef struct Player {
    float x, y;
    float angle;
    float speed;
    float radius;
    int num_points;
} Player;

typedef struct Mouse {
    bool is_walking;
    float sensitivity;
} Mouse;

void control_walking(float angle, float speed, float* real_x, float* real_y);
void move_player(Player* player, float dx, float dy, int map[][10]);
void update_mouse(Player* player, float sensitivity, int screenWidth, int screenHeight);

#endif