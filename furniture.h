#ifndef FURNITURE_H
#define FURNITURE_H

#include "raylib.h"

#define MAX_FURNITURE 37

typedef enum {
    FURN_BED,
    FURN_TABLE,
    FURN_WARDROBE,
    FURN_BOOKCASE,
    FURN_LONGBOOKCASE,
    FURN_SHELF,
    FURN_BIGSHELF,
    FURN_DESK,
    FURN_LOCKER,
    FURN_FLOWER,
    FURN_BOX
} FurnitureType;

// Индексы граней (для удобства)
#define FURN_FACE_FRONT 0
#define FURN_FACE_BACK  1
#define FURN_FACE_LEFT  2
#define FURN_FACE_RIGHT 3
#define FURN_FACE_TOP   4

typedef struct {
    int textures[5];// front, back, left, right, top
    int alt_textures[5];
} FurnitureTypeData;

extern FurnitureTypeData furniture_types[];

typedef struct {
    int id;
    FurnitureType type;
    float x, y;
    float width, depth;
    float height;
    bool is_solid;
    bool is_interactable;
    int item_to_give;
    bool interacted;
    int texture_override[5]; 
} Furniture;

extern Furniture furniture_list[MAX_FURNITURE];
extern int furniture_count;

Furniture* GetFAtPoint(float worldX, float worldY);
void AddFurniture(int id, FurnitureType type, float x, float y,
    float width, float depth, float height,
    bool solid, bool interactable, int item);
void InitAllFurniture();

#endif