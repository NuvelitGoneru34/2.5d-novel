#include "furniture.h"
#include <math.h>

Furniture furniture_list[MAX_FURNITURE];
int furniture_count = 0;

Furniture* GetFAtPoint(float worldX, float worldY) {
	for (int i = 0; i < furniture_count; i++) {
		Furniture* furniture = &furniture_list[i];
		if (worldX >= furniture->x && worldX < furniture->x + furniture->width &&
			worldY >= furniture->y && worldY < furniture->y + furniture->depth) {
			return furniture;
		}
	}
	return NULL;
}