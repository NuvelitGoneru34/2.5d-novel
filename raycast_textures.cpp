#include "raycast.h"

Texture2D Textures[MAX_TEXTURES];

void InitTextures() {
	Textures[0] = LoadTexture("textures/wall.png");
	Textures[1] = LoadTexture("textures/wallpaper1.png");
	Textures[2] = LoadTexture("textures/wallpaper2.png");
	Textures[3] = LoadTexture("textures/wallpaper3.png");
	Textures[4] = LoadTexture("textures/heavywall.png");
	Textures[5] = LoadTexture("textures/medicinewall.png");
	Textures[6] = LoadTexture("textures/librarywall.png");
	Textures[7] = LoadTexture("textures/door.png");
	Textures[8] = LoadTexture("textures/floor.png");
	Textures[9] = LoadTexture("textures/ceil.png");
	Textures[10] = LoadTexture("textures/medicinefloor.png");
	Textures[11] = LoadTexture("textures/medicineceil.png");
	Textures[12] = LoadTexture("textures/libraryfloor.png");
	Textures[13] = LoadTexture("textures/libraryceil.png");
	Textures[14] = LoadTexture("textures/heavyfloor.png");
	Textures[15] = LoadTexture("textures/heavyceil.png");
	Textures[16] = LoadTexture("textures/woodfloor.png");
	Textures[17] = LoadTexture("textures/darkwoodfloor.png");
	Textures[18] = LoadTexture("textures/stonefloor.png");

	Textures[19] = LoadTexture("textures/bedtop.png");
	Textures[20] = LoadTexture("textures/bedside.png");
	Textures[21] = LoadTexture("textures/tabletop.png");
	Textures[22] = LoadTexture("textures/tablefront.png");
	Textures[23] = LoadTexture("textures/tableside.png");
	Textures[24] = LoadTexture("textures/tablefront_alt.png");
	Textures[25] = LoadTexture("textures/wardrobefront.png");
	Textures[26] = LoadTexture("textures/wardrobeside.png");
	Textures[27] = LoadTexture("textures/desctop.png");
	Textures[28] = LoadTexture("textures/descfront.png");
	Textures[29] = LoadTexture("textures/descside.png");
	Textures[30] = LoadTexture("textures/shelffront.png");
	Textures[31] = LoadTexture("textures/shelfside.png");
	Textures[32] = LoadTexture("textures/bigshelf.png");
	Textures[33] = LoadTexture("textures/bookcasefront.png");
	Textures[34] = LoadTexture("textures/bookcaseside.png");
	Textures[35] = LoadTexture("textures/longbookcasefront.png");
	Textures[36] = LoadTexture("textures/medicinefront.png");
	Textures[37] = LoadTexture("textures/medicineside.png");
	Textures[38] = LoadTexture("textures/flower.png");
	Textures[39] = LoadTexture("textures/box.png");
	Textures[40] = LoadTexture("textures/bedtopupsidedown.png");
	Textures[41] = LoadTexture("textures/bedtopright.png");
}