#ifndef PLAYER_H
#define PLAYER_H

#include "raylib.h"
#include "map.h"
#include <math.h>

typedef struct Player {
    float x, y;
    float angle;
    float speed;
    bool is_running;
    float acceleration;
    float radius;
    int num_points;
    float fov;
} Player;

typedef struct Mouse {
    bool is_walking;
    float sensitivity;
} Mouse;

void control_player(Player* player, float* real_x, float* real_y, Cell map[MAP_HEIGHT][MAP_WIDTH], DoorState doors[MAP_HEIGHT][MAP_WIDTH]);
void move_player(Player* player, float dx, float dy, Cell map[MAP_HEIGHT][MAP_WIDTH]);
void update_mouse(Player* player, float sensitivity, int screenWidth, int screenHeight);
void interact(Player* player, Cell map[MAP_HEIGHT][MAP_WIDTH], DoorState doors[MAP_HEIGHT][MAP_WIDTH]);

#endif