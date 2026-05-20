#ifndef FURNITURE_H
#define FURNITURE_H

#include "raylib.h"

#define MAX_FURNITURE 50

typedef struct {
	int id;
	float width, height;
	float x, y;
	int texture_id;
	int alt_texture_id;
	bool is_solid;
	bool is_interactable;
	int item_to_give;
} Furniture;

extern Furniture furniture_list[MAX_FURNITURE];
extern int furniture_count;

Furniture* GetFAtPoint(float worldX, float worldY);

#endif