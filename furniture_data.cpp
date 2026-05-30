#include "furniture.h"

FurnitureTypeData furniture_types[] = {
    // FURN_BED
    {{20,20,20,20,19}, {20,20,20,20,19}},
    // FURN_TABLE
    {{22,23,23,23,21}, {24,23,23,23,21}},
    // FURN_WARDROBE
    {{26,26,26,25,0}, {26,26,26,25,0}},
    // FURN_BOOKCASE
    {{33,33,33,33,0}, {33,33,33,33,0}},
    // FURN_LONGBOOKCASE
    {{35,35,35,35,0}, {35,35,35,35,0}},
    // FURN_SHELF
    {{30,30,30,30,0}, {30,30,30,30,0}},
    // FURN_BIGSHELF
    {{32,32,32,32,0}, {32,32,32,32,0}},
    // FURN_DESK
    {{29,29,28,28,27}, {29,28,29,28,27}},
    // FURN_LOCKER
    {{36,36,36,36,0}, {36,36,36,36,0}},
    // FURN_FLOWER
    {{38,38,38,38,0}, {38,38,38,38,0}},
    // FURN_BOX
    {{39,39,39,39,0}, {39,39,39,39,0}}
};

void AddFurniture(int id, FurnitureType type, float x, float y,
    float width, float depth, float height,
    bool solid, bool interactable, int item) {
    if (furniture_count >= MAX_FURNITURE) return;
    Furniture* f = &furniture_list[furniture_count];
    f->id = id;
    f->type = type;
    f->x = x;
    f->y = y;
    f->width = width;
    f->depth = depth;
    f->height = height;
    f->is_solid = solid;
    f->is_interactable = interactable;
    f->item_to_give = item;
    f->interacted = false;
    for (int i = 0; i < 5; i++) f->texture_override[i] = -1;
    furniture_count++;
}

void InitAllFurniture() {
    //  ŒÃÕ¿“¿ √≈–Œﬂ
    AddFurniture(0, FURN_DESK, 3.2f, 2.0f, 0.8f, 2.0f, 0.4f, true, false, 0);
    AddFurniture(1, FURN_FLOWER, 3.2f, 1.2f, 0.6f, 0.6f, 0.6f, true, false, 0);
    AddFurniture(2, FURN_TABLE, 2.05f, 1.0f, 0.9f, 0.8f, 0.4f, true, true, 0);
    AddFurniture(3, FURN_BED, 1.0f, 1.0f, 0.9f, 2.0f, 0.3f, true, false, 0);
    AddFurniture(4, FURN_WARDROBE, 1.0f, 3.1f, 0.8f, 1.9f, 0.9f, true, false, 0);

    // ∆»À¿ﬂ  ŒÃÕ¿“¿ 1
    AddFurniture(5, FURN_FLOWER, 13.2f, 1.2f, 0.6f, 0.6f, 0.6f, true, false, 0);
    AddFurniture(6, FURN_TABLE, 14.05f, 4.2f, 0.9f, 0.8f, 0.3f, true, true, 0);
    furniture_list[6].texture_override[FURN_FACE_BACK] = 22;
    AddFurniture(7, FURN_BED, 13.0f, 3.0f, 0.9f, 2.0f, 0.3f, true, false, 0);
    furniture_list[7].texture_override[FURN_FACE_TOP] = 40;
    AddFurniture(8, FURN_WARDROBE, 14.0f, 1.0f, 2.0f, 0.8f, 0.9f, true, false, 0);
    furniture_list[8].texture_override[FURN_FACE_FRONT] = 25;
    furniture_list[8].texture_override[FURN_FACE_LEFT] = 26;

    // ∆»À¿ﬂ  ŒÃÕ¿“¿ 2
    AddFurniture(9, FURN_DESK, 32.0f, 9.0f, 2.0f, 0.8f, 0.4f, true, true, 0);
    furniture_list[9].texture_override[FURN_FACE_FRONT] = 28;
    furniture_list[9].texture_override[FURN_FACE_BACK] = 28;
    furniture_list[9].texture_override[FURN_FACE_LEFT] = 29;
    furniture_list[9].texture_override[FURN_FACE_RIGHT] = 29;
    AddFurniture(10, FURN_FLOWER, 34.2f, 9.2f, 0.6f, 0.6f, 0.6f, true, false, 0);
    AddFurniture(11, FURN_TABLE, 34.2f, 10.05f, 0.8f, 0.9f, 0.3f, true, false, 0);
    furniture_list[11].texture_override[FURN_FACE_FRONT] = 23;
    furniture_list[11].texture_override[FURN_FACE_LEFT] = 22;
    AddFurniture(12, FURN_BED, 33.0f, 11.1f, 2.0f, 0.9f, 0.3f, true, false, 0);
    furniture_list[12].texture_override[FURN_FACE_TOP] = 41;
    AddFurniture(13, FURN_WARDROBE, 31.0f, 11.2f, 2.0f, 0.8f, 0.9f, true, false, 0);
    furniture_list[13].texture_override[FURN_FACE_BACK] = 25;
    furniture_list[13].texture_override[FURN_FACE_RIGHT] = 26;

    // “≈’Õ»◊≈— Œ≈ œŒÃ≈Ÿ≈Õ»≈
    AddFurniture(14, FURN_SHELF, 17.0f, 1.0f, 0.8f, 2.0f, 0.75f, true, true, 0);
    AddFurniture(15, FURN_SHELF, 17.0f, 3.0f, 0.8f, 2.0f, 0.75f, true, false, 0);
    AddFurniture(16, FURN_BOX, 18.1f, 1.1f, 0.9f, 0.9f, 0.9f, true, false, 0);

    // — À¿ƒ
    AddFurniture(17, FURN_SHELF, 31.0f, 13.0f, 2.0f, 0.8f, 0.75f, true, false, 0);
    AddFurniture(18, FURN_SHELF, 33.0f, 13.0f, 2.0f, 0.8f, 0.75f, true, false, 0);
    AddFurniture(19, FURN_SHELF, 34.2f, 14.0f, 0.8f, 2.0f, 0.75f, true, false, 0);
    AddFurniture(20, FURN_SHELF, 34.2f, 16.0f, 0.8f, 2.0f, 0.75f, true, false, 0);
    AddFurniture(21, FURN_SHELF, 34.2f, 18.0f, 0.8f, 2.0f, 0.75f, true, false, 0);
    AddFurniture(22, FURN_BIGSHELF, 31.0f, 15.1f, 1.9f, 1.8f, 0.75f, true, false, 0);
    AddFurniture(23, FURN_DESK, 31.0f, 19.0f, 2.0f, 0.8f, 0.4f, true, false, 0);
    furniture_list[23].texture_override[FURN_FACE_FRONT] = 28;
    furniture_list[23].texture_override[FURN_FACE_BACK] = 28;
    furniture_list[23].texture_override[FURN_FACE_LEFT] = 29;
    furniture_list[23].texture_override[FURN_FACE_RIGHT] = 29;

    // ¡»¡À»Œ“≈ ¿
    AddFurniture(24, FURN_DESK, 20.0f, 24.2f, 2.0f, 0.8f, 0.4f, true, false, 0);
    furniture_list[24].texture_override[FURN_FACE_FRONT] = 28;
    furniture_list[24].texture_override[FURN_FACE_BACK] = 28;
    furniture_list[24].texture_override[FURN_FACE_LEFT] = 29;
    furniture_list[24].texture_override[FURN_FACE_RIGHT] = 29;
    AddFurniture(25, FURN_FLOWER, 23.2f, 30.2f, 0.6f, 0.6f, 0.6f, true, false, 0);
    AddFurniture(26, FURN_BOOKCASE, 21.0f, 30.2f, 2.0f, 0.8f, 0.75f, true, false, 0);
    AddFurniture(27, FURN_BOOKCASE, 24.0f, 30.2f, 2.0f, 0.8f, 0.75f, true, false, 0);
    AddFurniture(28, FURN_BOOKCASE, 20.0f, 28.0f, 0.8f, 2.0f, 0.75f, true, false, 0);
    AddFurniture(29, FURN_BOOKCASE, 26.2f, 28.0f, 0.8f, 2.0f, 0.75f, true, true, 0);
    AddFurniture(30, FURN_BOOKCASE, 26.2f, 24.0f, 0.8f, 2.0f, 0.75f, true, false, 0);
    AddFurniture(31, FURN_LONGBOOKCASE, 23.0f, 23.0f, 3.0f, 0.8f, 0.75f, true, false, 0);
    AddFurniture(32, FURN_LONGBOOKCASE, 22.0f, 26.1f, 3.0f, 0.8f, 0.75f, true, false, 0);
    AddFurniture(33, FURN_LONGBOOKCASE, 22.0f, 28.1f, 3.0f, 0.8f, 0.75f, true, false, 0);

    // Ã≈ƒ¡ÀŒ 
    AddFurniture(34, FURN_DESK, 2.2f, 15.0f, 0.8f, 2.0f, 0.4f, true, false, 0);
    AddFurniture(35, FURN_LOCKER, 1.0f, 13.0f, 2.0f, 0.8f, 0.9f, true, false, 0);
    AddFurniture(36, FURN_LOCKER, 3.0f, 13.0f, 2.0f, 0.8f, 0.9f, true, true, 0);
}