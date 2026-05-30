#ifndef MAP_H
#define MAP_H

#include "furniture.h"

#define SCREEN_WIDTH  1920
#define SCREEN_HEIGHT 1080

#define MAP_WIDTH  36
#define MAP_HEIGHT 40

typedef enum {
	CELL_EMPTY = 0,
	CELL_WALL = 1,
	CELL_DOOR = 2,
	CELL_LOCKED_DOOR = 3,
} CellType;

#define FACE_NORTH 0
#define FACE_SOUTH 1
#define FACE_WEST 2
#define FACE_EAST 3

typedef struct {
	int wall[4];
	int floor;
	int ceil;
	int door_leaf;
	int door_side;
} CellTexture;

typedef struct {
	CellType type;
	CellTexture texture;
	Furniture* furniture;
} Cell;

typedef struct {
	bool is_open;
	bool is_opening;
	float offset;
	float dir;
} DoorState;

extern Cell map[MAP_HEIGHT][MAP_WIDTH];
extern DoorState doors[MAP_HEIGHT][MAP_WIDTH];

bool IsSolid(Cell cell, DoorState *door);
void UpdateDoors(DoorState door[MAP_HEIGHT][MAP_WIDTH]);

#endif