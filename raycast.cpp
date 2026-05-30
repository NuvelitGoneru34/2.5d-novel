#include "raycast.h"
#include "furniture.h"
#include <stdlib.h>
#include <math.h>

float zBuffer[SCREEN_WIDTH];
const int STEP = 4;
const float MAX_DIST = 15.0f;

Color* floorPixels[MAX_TEXTURES] = { NULL };
int floorTexWidth[MAX_TEXTURES] = { 0 };
int floorTexHeight[MAX_TEXTURES] = { 0 };

Color* ceilPixels[MAX_TEXTURES] = { NULL };
int ceilTexWidth[MAX_TEXTURES] = { 0 };
int ceilTexHeight[MAX_TEXTURES] = { 0 };

Color GetPixelFromArray(Color* pixels, int width, int height, int x, int y) {
    if (pixels == NULL) return BLACK;

    if (x < 0) x = (x % width + width) % width;
    else x = x % width;

    if (y < 0) y = (y % height + height) % height;
    else y = y % height;

    return pixels[y * width + x];
}

bool IntersectFurnitureAABB(Player* player, float ray_dirX, float ray_dirY,
    Furniture* f, float maxDist, float* out_dist, int* out_face, float* out_wallU) {

    float invDirX;
    float invDirY;

    if (fabsf(ray_dirX) > 0.00001f) invDirX = 1.0f / ray_dirX;
    else invDirX = 100000.0f;

    if (fabsf(ray_dirY) > 0.00001f) invDirY = 1.0f / ray_dirY;
    else invDirY = 100000.0f;

    float t1 = (f->x - player->x) * invDirX;
    float t2 = (f->x + f->width - player->x) * invDirX;
    float t3 = (f->y - player->y) * invDirY;
    float t4 = (f->y + f->depth - player->y) * invDirY;

    float tmin = fmaxf(fminf(t1, t2), fminf(t3, t4));
    float tmax = fminf(fmaxf(t1, t2), fmaxf(t3, t4));

    if (tmax < 0) return false;
    if (tmin > tmax) return false;
    if (tmin < 0) tmin = 0;
    if (tmin > maxDist) return false;

    float hitX = player->x + tmin * ray_dirX;
    float hitY = player->y + tmin * ray_dirY;

    int face;
    const float EPS = 0.001f;
    if (fabsf(hitX - f->x) < EPS) face = FURN_FACE_LEFT;
    else if (fabsf(hitX - (f->x + f->width)) < EPS) face = FURN_FACE_RIGHT;
    else if (fabsf(hitY - f->y) < EPS) face = FURN_FACE_BACK;
    else face = FURN_FACE_FRONT;

    float wallU;
    if (face == FURN_FACE_FRONT || face == FURN_FACE_BACK) {
        float u = hitX - f->x;
        wallU = u / f->width;
        if (face == FURN_FACE_BACK) wallU = 1.0f - wallU;
    }
    else {
        float u = hitY - f->y;
        wallU = u / f->depth;
        if (face == FURN_FACE_RIGHT) wallU = 1.0f - wallU;
    }

    *out_dist = tmin;
    *out_face = face;
    *out_wallU = wallU;
    return true;
}

void RenderSingleFurniture(Player* player, Furniture* f, int offsetY) {
    float half_fov = player->fov / 2.0f;
    float start_angle = player->angle - half_fov;

    bool hasVisibleColumns = false;

    for (int col = 0; col < SCREEN_WIDTH; col += STEP) {
        int blockW;
        if (col + STEP < SCREEN_WIDTH) blockW = STEP;
        else blockW = SCREEN_WIDTH - col;

        float midX = col + blockW / 2.0f;
        float ray_angle = start_angle + (float)midX / SCREEN_WIDTH * player->fov;

        float furnDist;
        int face;
        float u;
        if (!IntersectFurnitureAABB(player, cosf(ray_angle), sinf(ray_angle), f, MAX_DIST, &furnDist, &face, &u))
            continue;

        if (furnDist >= zBuffer[col]) continue;

        hasVisibleColumns = true;

        int texIdx;
        if (f->texture_override[face] != -1) texIdx = f->texture_override[face];
        else if (f->interacted) texIdx = furniture_types[f->type].alt_textures[face];
        else texIdx = furniture_types[f->type].textures[face];

        if (texIdx < 0) continue;
        if (texIdx >= MAX_TEXTURES) continue;

        float perpDist = furnDist * cosf(ray_angle - player->angle);
        if (perpDist < 0.01f) perpDist = 0.01f;

        float fullHeight = SCREEN_HEIGHT / perpDist;
        int baseY = (int)(SCREEN_HEIGHT / 2 + fullHeight / 2 + offsetY);
        int wallHeight = (int)(fullHeight * f->height);
        int drawStart = baseY - wallHeight;
        int drawEnd = baseY;

        int texW = floorTexWidth[texIdx];
        int texH = floorTexHeight[texIdx];

        int startY = -STEP;
        int endY = SCREEN_HEIGHT + STEP;
        for (int y = startY; y < endY; y += STEP) {
            int blockH;
            if (y + STEP < endY) blockH = STEP + 1;
            else blockH = endY - y;

            if (y + blockH <= drawStart) continue;
            if (y >= drawEnd) continue;

            int visibleTop;
            if (0 > y) visibleTop = 0;
            else visibleTop = y;

            int visibleBottom;
            if (SCREEN_HEIGHT < y + blockH) visibleBottom = SCREEN_HEIGHT;
            else visibleBottom = y + blockH;

            if (visibleTop >= visibleBottom) continue;

            float v = (float)(y - drawStart) / wallHeight;
            int texY = (int)(v * texH) % texH;
            int texX = (int)(u * texW) % texW;
            Color color = GetPixelFromArray(floorPixels[texIdx], texW, texH, texX, texY);

            DrawRectangle(col, visibleTop, blockW, visibleBottom - visibleTop, color);
        }
    }

    if (f->height <= 0.0f) return;

    int topTexIdx;

    if (f->texture_override[FURN_FACE_TOP] != -1) topTexIdx = f->texture_override[FURN_FACE_TOP];
    else if (f->interacted) topTexIdx = furniture_types[f->type].alt_textures[FURN_FACE_TOP];
    else topTexIdx = furniture_types[f->type].textures[FURN_FACE_TOP];

    if (topTexIdx < 0) return;
    if (topTexIdx >= MAX_TEXTURES) return;

    float cx = f->x + f->width / 2.0f;
    float cy = f->y + f->depth / 2.0f;
    float dx = cx - player->x;
    float dy = cy - player->y;
    float distToObj = sqrtf(dx * dx + dy * dy);
    float angleToObj = atan2f(dy, dx) - player->angle;

    while (angleToObj > PI) angleToObj -= 2 * PI;
    while (angleToObj < -PI) angleToObj += 2 * PI;

    float perpDist = distToObj * cosf(angleToObj);
    if (perpDist < 0.01f) perpDist = 0.01f;

    float wallH = SCREEN_HEIGHT / perpDist;
    int baseY = (int)(SCREEN_HEIGHT / 2 + wallH / 2 + offsetY);
    int topY = baseY - (int)(wallH * f->height);

    if (topY < SCREEN_HEIGHT / 2) return;

    float minScreenX = SCREEN_WIDTH;
    float maxScreenX = 0;
    float cornersX[4] = { f->x, f->x + f->width, f->x + f->width, f->x };
    float cornersY[4] = { f->y, f->y, f->y + f->depth, f->y + f->depth };
    bool anyCornerInFront = false;

    for (int c = 0; c < 4; c++) {
        float dx = cornersX[c] - player->x;
        float dy = cornersY[c] - player->y;

        float transX = dx * cosf(player->angle) + dy * sinf(player->angle);
        float transY = -dx * sinf(player->angle) + dy * cosf(player->angle);

        if (transX <= 0.01f) transX = 0.01f;
        else anyCornerInFront = true;

        float screenX = (SCREEN_WIDTH / 2.0f) * (1.0f + transY / (transX * tanf(half_fov)));
        if (screenX < minScreenX) minScreenX = screenX;
        if (screenX > maxScreenX) maxScreenX = screenX;
    }
    if (!anyCornerInFront) return;

    int left;
    if (0 > (int)minScreenX) left = 0;
    else left = (int)minScreenX;

    int right;
    if (SCREEN_WIDTH - 1 < (int)maxScreenX) right = SCREEN_WIDTH - 1;
    else right = (int)maxScreenX;

    if (left > right) return;

    for (int y = 0; y < SCREEN_HEIGHT; y += STEP) {
        int blockH;
        if (y + STEP < SCREEN_HEIGHT) blockH = STEP;
        else blockH = SCREEN_HEIGHT - y;

        int denom = y - offsetY - SCREEN_HEIGHT / 2;
        if (denom == 0) continue;

        float planeDist = (SCREEN_HEIGHT * (0.5f - f->height)) / (float)denom;
        if (planeDist < 0.01f) continue;
        if (planeDist > MAX_DIST) continue;

        for (int x = left; x <= right; x += STEP) {
            int blockW;
            if (x + STEP < SCREEN_WIDTH) blockW = STEP;
            else blockW = SCREEN_WIDTH - x;

            int midX = x + blockW / 2;

            float rayAngle = start_angle + (float)midX / SCREEN_WIDTH * player->fov;
            float correctedDist = planeDist / cosf(rayAngle - player->angle);

            if (correctedDist > zBuffer[midX]) continue;

            int drawTop = y + offsetY;
            int drawBottom = drawTop + blockH;

            if (0 > drawTop) drawTop = 0;
            if (SCREEN_HEIGHT < drawBottom) drawBottom = SCREEN_HEIGHT;

            float worldX = player->x + correctedDist * cosf(rayAngle);
            float worldY = player->y + correctedDist * sinf(rayAngle);

            if (worldX < f->x) continue;
            if (worldX > f->x + f->width) continue;
            if (worldY < f->y) continue;
            if (worldY > f->y + f->depth) continue;

            int texW = floorTexWidth[topTexIdx];
            int texH = floorTexHeight[topTexIdx];

            int texX = (int)(((worldX - f->x) / f->width) * texW);
            int texY = (int)(((worldY - f->y) / f->depth) * texH);

            if (drawTop < drawBottom) {
                Color color = GetPixelFromArray(floorPixels[topTexIdx], texW, texH, texX, texY);
                DrawRectangle(x, drawTop, blockW, drawBottom - drawTop, color);
            }
        }
    }
}

void raycast(Player* player) {
    BeginDrawing();
    ClearBackground(BLACK);

    float half_fov = player->fov / 2.0f;
    float start_angle = player->angle - half_fov;

    float bobOffset = 0.0f;
    if (player->speed > 0.001f) {
        float amplitude;
        if (player->is_running) amplitude = 3.0f;
        else amplitude = 1.5f;

        float frequency = 10.0f;
        float time = (float)GetTime();
        bobOffset = sinf(time * frequency) * amplitude * (player->speed / player->base_speed);
    }
    int offsetY = (int)bobOffset;

    for (int i = 0; i < SCREEN_WIDTH; i++) zBuffer[i] = MAX_DIST;

    int numBlocks = (SCREEN_WIDTH + STEP - 1) / STEP;
    float* wallDist = (float*)malloc(numBlocks * sizeof(float));
    int* wallTex = (int*)malloc(numBlocks * sizeof(int));
    int* wallFace = (int*)malloc(numBlocks * sizeof(int));
    float* wallU = (float*)malloc(numBlocks * sizeof(float));

    for (int bx = 0; bx < numBlocks; bx++) {
        int col = bx * STEP;
        int blockW;
        if (col + STEP < SCREEN_WIDTH) blockW = STEP;
        else blockW = SCREEN_WIDTH - col;

        float midX = col + blockW / 2.0f;
        float ray_angle = start_angle + (float)midX / SCREEN_WIDTH * player->fov;
        float ray_dirX = cosf(ray_angle);
        float ray_dirY = sinf(ray_angle);

        int mapX = (int)player->x, mapY = (int)player->y;
        float delta_distX = fabsf(1.0f / ray_dirX), delta_distY = fabsf(1.0f / ray_dirY);
        float side_distX, side_distY;
        int stepX, stepY;

        if (ray_dirX < 0) {
            stepX = -1;
            side_distX = (player->x - mapX) * delta_distX;
        }
        else {
            stepX = 1;
            side_distX = (mapX + 1.0f - player->x) * delta_distX;
        }

        if (ray_dirY < 0) {
            stepY = -1;
            side_distY = (player->y - mapY) * delta_distY;
        }
        else {
            stepY = 1;
            side_distY = (mapY + 1.0f - player->y) * delta_distY;
        }

        bool hit = false;
        bool is_not_side = false;
        float dist = MAX_DIST;
        Cell cell;

        while (true) {
            if (side_distX < side_distY) {
                dist = side_distX;
                side_distX += delta_distX;
                mapX += stepX;
                is_not_side = 0;
            }
            else {
                dist = side_distY;
                side_distY += delta_distY;
                mapY += stepY;
                is_not_side = 1;
            }

            if (dist > MAX_DIST) break;
            if (mapX < 0) break;
            if (mapX >= MAP_WIDTH) break;
            if (mapY < 0) break;
            if (mapY >= MAP_HEIGHT) break;

            cell = map[mapY][mapX];
            if (cell.type == CELL_WALL || cell.type == CELL_LOCKED_DOOR) {
                hit = true;
                if (cell.type == CELL_WALL) {
                    if (is_not_side == 0) {
                        if (ray_dirX > 0) wallFace[bx] = FACE_WEST;
                        else wallFace[bx] = FACE_EAST;
                    }
                    else {
                        if (ray_dirY > 0) wallFace[bx] = FACE_NORTH;
                        else wallFace[bx] = FACE_SOUTH;
                    }
                    wallTex[bx] = cell.texture.wall[wallFace[bx]];
                }
                else {
                    wallTex[bx] = cell.texture.door_leaf;
                    wallFace[bx] = 0;
                }

                if (is_not_side == 0) wallU[bx] = player->y + dist * ray_dirY;
                else wallU[bx] = player->x + dist * ray_dirX;

                wallU[bx] -= floorf(wallU[bx]);
                break;
            }
            else if (cell.type == CELL_DOOR) {
                DoorState* door = &doors[mapY][mapX];
                if (!door->is_open || door->offset < 1.0f) {
                    hit = true;
                    wallTex[bx] = cell.texture.door_leaf;
                    wallFace[bx] = 0;

                    if (is_not_side == 0) wallU[bx] = player->y + dist * ray_dirY;
                    else wallU[bx] = player->x + dist * ray_dirX;

                    wallU[bx] -= floorf(wallU[bx]);
                    break;
                }
            }
        }

        if (hit) {
            wallDist[bx] = dist;
            for (int fillX = col; fillX < col + blockW && fillX < SCREEN_WIDTH; fillX++) {
                zBuffer[fillX] = dist;
            }
        }
        else {
            wallDist[bx] = MAX_DIST;
            wallTex[bx] = -1;
        }
    }

    int startY = -STEP, endY = SCREEN_HEIGHT + STEP;
    for (int y = startY; y < endY; y += STEP) {
        int blockH;
        if (y + STEP < endY) blockH = STEP + 1;
        else blockH = endY - y;

        int drawY = y + offsetY;
        if (drawY + blockH <= 0) continue;
        if (drawY >= SCREEN_HEIGHT) continue;

        int visibleTop;
        if (0 > drawY) visibleTop = 0;
        else visibleTop = drawY;

        int visibleBottom;
        if (SCREEN_HEIGHT < drawY + blockH) visibleBottom = SCREEN_HEIGHT;
        else visibleBottom = drawY + blockH;

        for (int x = 0; x < SCREEN_WIDTH; x += STEP) {
            int blockW;
            if (x + STEP < SCREEN_WIDTH) blockW = STEP + 1;
            else blockW = SCREEN_WIDTH - x;

            int midX = x + blockW / 2;
            float rayAngle = start_angle + (float)midX / SCREEN_WIDTH * player->fov;
            float correctedDist, rawDist;

            if (y < SCREEN_HEIGHT / 2) {
                float rowDistance = (float)SCREEN_HEIGHT / (SCREEN_HEIGHT - 2.0f * y);
                correctedDist = rowDistance / cosf(rayAngle - player->angle);
                if (correctedDist > zBuffer[midX]) continue;
                rawDist = correctedDist;
            }
            else {
                float rowDistance = (float)SCREEN_HEIGHT / (2.0f * y - SCREEN_HEIGHT);
                correctedDist = rowDistance / cosf(rayAngle - player->angle);
                if (correctedDist > zBuffer[midX]) continue;
                rawDist = correctedDist;
            }

            if (rawDist > MAX_DIST) continue;

            float worldX = player->x + rawDist * cosf(rayAngle);
            float worldY = player->y + rawDist * sinf(rayAngle);
            int cellX = (int)worldX, cellY = (int)worldY;

            if (cellX < 0) continue;
            if (cellX >= MAP_WIDTH) continue;
            if (cellY < 0) continue;
            if (cellY >= MAP_HEIGHT) continue;

            Cell cell = map[cellY][cellX];
            int texIdx;
            if (y < SCREEN_HEIGHT / 2) texIdx = cell.texture.ceil;
            else texIdx = cell.texture.floor;

            if (texIdx <= 0) continue;
            if (texIdx >= MAX_TEXTURES) continue;

            Color* pixels;
            if (y < SCREEN_HEIGHT / 2) pixels = ceilPixels[texIdx];
            else pixels = floorPixels[texIdx];

            int texW = floorTexWidth[texIdx];
            int texH = floorTexHeight[texIdx];
            int texX = (int)((worldX - cellX) * texW) % texW;
            int texY = (int)((worldY - cellY) * texH) % texH;
            Color color = GetPixelFromArray(pixels, texW, texH, texX, texY);
            DrawRectangle(x, visibleTop, blockW, visibleBottom - visibleTop, color);
        }
    }

    for (int bx = 0; bx < numBlocks; bx++) {
        if (wallTex[bx] < 0) continue;

        int col = bx * STEP;
        int blockW;
        if (col + STEP < SCREEN_WIDTH) blockW = STEP;
        else blockW = SCREEN_WIDTH - col;

        float ray_angle = start_angle + (float)(col + blockW / 2) / SCREEN_WIDTH * player->fov;
        float perpDist = wallDist[bx] * cosf(ray_angle - player->angle);
        if (perpDist < 0.01f) perpDist = 0.01f;

        int wallHeight = (int)(SCREEN_HEIGHT / perpDist);
        int drawStart = (SCREEN_HEIGHT - wallHeight) / 2 + offsetY;
        int drawEnd = drawStart + wallHeight;
        int texW = floorTexWidth[wallTex[bx]];
        int texH = floorTexHeight[wallTex[bx]];

        for (int y = startY; y < endY; y += STEP) {
            int blockH;
            if (y + STEP < endY) blockH = STEP + 1;
            else blockH = endY - y;

            if (y + blockH <= drawStart) continue;
            if (y >= drawEnd) continue;

            int visibleTop;
            if (0 > y) visibleTop = 0;
            else visibleTop = y;

            int visibleBottom;
            if (SCREEN_HEIGHT < y + blockH) visibleBottom = SCREEN_HEIGHT;
            else visibleBottom = y + blockH;

            float v = (float)(y - drawStart) / wallHeight;
            int texY = (int)(v * texH) % texH;
            int texX = (int)(wallU[bx] * texW) % texW;
            Color color = GetPixelFromArray(floorPixels[wallTex[bx]], texW, texH, texX, texY);
            DrawRectangle(col, visibleTop, blockW, visibleBottom - visibleTop, color);
        }
    }

    int spriteCount = 0;
    int spriteOrder[MAX_FURNITURE];
    float spriteDist[MAX_FURNITURE];

    for (int i = 0; i < furniture_count; i++) {
        Furniture* f = &furniture_list[i];
        float cx = f->x + f->width / 2.0f;
        float cy = f->y + f->depth / 2.0f;
        float dx = cx - player->x;
        float dy = cy - player->y;
        float dist = dx * dx + dy * dy;

        spriteOrder[spriteCount] = i;
        spriteDist[spriteCount] = dist;
        spriteCount++;
    }

    for (int i = 0; i < spriteCount - 1; i++) {
        for (int j = 0; j < spriteCount - i - 1; j++) {
            if (spriteDist[j] < spriteDist[j + 1]) {
                float td = spriteDist[j];
                spriteDist[j] = spriteDist[j + 1];
                spriteDist[j + 1] = td;

                int ti = spriteOrder[j];
                spriteOrder[j] = spriteOrder[j + 1];
                spriteOrder[j + 1] = ti;
            }
        }
    }

    for (int s = 0; s < spriteCount; s++) {
        RenderSingleFurniture(player, &furniture_list[spriteOrder[s]], offsetY);
    }

    free(wallDist);
    free(wallTex);
    free(wallFace);
    free(wallU);
    EndDrawing();
}

void PrepareTextures() {
    for (int i = 0; i < MAX_TEXTURES; i++) {
        if (Textures[i].id > 0) {
            Image img = LoadImageFromTexture(Textures[i]);
            floorPixels[i] = LoadImageColors(img);
            floorTexWidth[i] = img.width;
            floorTexHeight[i] = img.height;
            ceilPixels[i] = LoadImageColors(img);
            ceilTexWidth[i] = img.width;
            ceilTexHeight[i] = img.height;
            UnloadImage(img);
        }
    }
}