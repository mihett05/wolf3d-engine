#include <iostream>
#include "CCamera.h"
#include "CTexture.h"

#define texWidth 64
#define texHeight 64

CCamera::CCamera(CFrameBuffer* buffer, CClock* clock, CMap* map)
  : buffer(buffer), clock(clock), map(map) {

    posX = map->spawnPosition.x + 0.5;
    posY = map->spawnPosition.y + 0.5;
    dirX = -1.0;
    dirY = 0.0;
    planeX = 0.0;
    planeY = 0.66;

    CTexture::initSigns();
    CTexture::loadFiles();
}


CFrameBuffer* CCamera::draw() {
    buffer->clear(CFrameBuffer::rgbToArgb(84, 84, 84, 255));

    for (int x = 0; x < buffer->w; x++) {
        double cameraX = (double)(2 * x) / (double)buffer->w - 1;
        double rayDirX = dirX + planeX * cameraX;
        double rayDirY = dirY + planeY * cameraX;

        int mapX = int(posX);
        int mapY = int(posY);

        double sideDistX;
        double sideDistY;

        double deltaDistX = abs(1 / rayDirX);
        double deltaDistY = abs(1 / rayDirY);
        double perpWallDist;

        int stepX;
        int stepY;

        bool hit = false;
        int side;

        CMapCell* cell = nullptr;

        if (rayDirX < 0) {
            stepX = -1;
            sideDistX = (posX - mapX) * deltaDistX;
        }
        else {
            stepX = 1;
            sideDistX = (mapX + 1.0 - posX) * deltaDistX;
        }
        if (rayDirY < 0) {
            stepY = -1;
            sideDistY = (posY - mapY) * deltaDistY;
        }
        else {
            stepY = 1;
            sideDistY = (mapY + 1.0 - posY) * deltaDistY;
        }

        while (!hit) {
            if (sideDistX < sideDistY) {
                sideDistX += deltaDistX;
                mapX += stepX;
                side = 0;
            }
            else {
                sideDistY += deltaDistY;
                mapY += stepY;
                side = 1;
            }

            cell = map->getCellOn(mapX, mapY);

            if (cell != nullptr && cell->type == BLOCK)
                hit = true;
        }

        if (side == 0) perpWallDist = (mapX - posX + (1 - stepX) / 2) / rayDirX;
        else perpWallDist = (mapY - posY + (1 - stepY) / 2) / rayDirY;

        int lineHeight = (int)(buffer->h / perpWallDist);

        int drawStart = -lineHeight / 2 + buffer->h / 2;
        if (drawStart < 0) drawStart = 0;
        int drawEnd = lineHeight / 2 + buffer->h / 2;
        if (drawEnd >= buffer->h) drawEnd = buffer->h - 1;
        char textureSign = 0;

        if (cell != nullptr && cell->type == BLOCK) {
            textureSign = cell->block->getTexture();
        } else continue;


        double wallX;
        if (side == 0) wallX = posY + perpWallDist * rayDirY;
        else wallX = posX + perpWallDist * rayDirX;
        wallX -= floor((wallX));

        int texX = int(wallX * double(texWidth));
        if (side == 0 && rayDirX > 0) texX = texWidth - texX - 1;
        if (side == 1 && rayDirY < 0) texX = texWidth - texX - 1;

        double step = 1.0 * texHeight / lineHeight;
        double texPos = (drawStart - buffer->h / 2 + lineHeight / 2) * step;

        vector<uint32_t>* texture = CTexture::getTexture(textureSign);
        for (int y = drawStart; y < drawEnd; y++) {
            int texY = (int)texPos & (texHeight - 1);
            texPos += step;
            uint32_t color = texture->at(texHeight * texY + texX);
            buffer->setPixel(Vector2u(x, y), color);
        }
    }

    for (uint32_t i = 0; i < map->entities->size(); ++i) {

    }

    double moveSpeed = getMoveSpeed(); //the constant value is in squares/second
    double rotSpeed = getRotationSpeed(); //the constant value is in radians/second

    const uint8_t* keyState = SDL_GetKeyboardState(NULL);
    if (keyState[SDL_SCANCODE_W]) {
        moveStraight(true, moveSpeed);
    }
    if (keyState[SDL_SCANCODE_S]) {
        moveStraight(false, moveSpeed);
    }
    if (keyState[SDL_SCANCODE_D]) {
        double oldDirX = dirX;
        dirX = dirX * cos(-rotSpeed) - dirY * sin(-rotSpeed);
        dirY = oldDirX * sin(-rotSpeed) + dirY * cos(-rotSpeed);
        double oldPlaneX = planeX;
        planeX = planeX * cos(-rotSpeed) - planeY * sin(-rotSpeed);
        planeY = oldPlaneX * sin(-rotSpeed) + planeY * cos(-rotSpeed);
    }
    if (keyState[SDL_SCANCODE_A]) {
        double oldDirX = dirX;
        dirX = dirX * cos(rotSpeed) - dirY * sin(rotSpeed);
        dirY = oldDirX * sin(rotSpeed) + dirY * cos(rotSpeed);
        double oldPlaneX = planeX;
        planeX = planeX * cos(rotSpeed) - planeY * sin(rotSpeed);
        planeY = oldPlaneX * sin(rotSpeed) + planeY * cos(rotSpeed);
    }
    return buffer;
}

bool CCamera::canMove(bool isForward, CMapCell* cell, CMapCell* cellNext, float diff, double dir) const {
    bool okDistance = diff <= 0.5 || diff > 1;
    bool okDir = isForward ? dir < 0 : dir >= 0;
    bool okBlockDistance = (diff >= 0.5 && okDir) || (okDistance && (isForward ? dir >= 0 : dir < 0));
    bool canMove = cell->type == EMPTY && (cellNext->type == EMPTY || (cellNext->type == BLOCK && okBlockDistance));
    return canMove;
}

void CCamera::moveStraight(bool isForward, double moveSpeed) {
    double x = posX + ((isForward? 1 : -1) * dirX * moveSpeed);
    double y = posY + ((isForward? 1 : -1) * dirY * moveSpeed);
    CMapCell* cellX = map->getCellOn(int(x), int(posY));
    CMapCell* cellY = map->getCellOn(int(posX), int(y));

    if (cellX && cellY) {
        double nextX = posX + dirX * moveSpeed;
        double nextY = posY + dirY * moveSpeed;
        if (isForward) {
            nextX += dirX >= 0 ? 1 : -1;
            nextY += dirY >= 0 ? 1 : -1;
        } else {
            nextX += dirX >= 0 ? -1 : 1;
            nextY += dirY >= 0 ? -1 : 1;
        }

        CMapCell* cellNextX = map->getCellOn(int(nextX), int(posY));
        CMapCell* cellNextY = map->getCellOn(int(posX), int(nextY));

        if (cellNextX && cellNextY) {
            float diffX = floorf(abs(int(posX + dirX * moveSpeed) - posX) * 10.0 + 0.5) / 10.0;
            bool canMoveX = canMove(isForward, cellX, cellNextX, diffX, dirX);

            float diffY = floorf(abs(int(posY + dirY * moveSpeed) - posY) * 10.0 + 0.5) / 10.0;
            bool canMoveY = canMove(isForward, cellY, cellNextY, diffY, dirY);

            if (isForward) {
                if (canMoveX) posX += dirX * moveSpeed;
                if (canMoveY) posY += dirY * moveSpeed;
            } else {
                if (canMoveX && canMoveY) {
                    posX -= dirX * moveSpeed;
                    posY -= dirY * moveSpeed;
                }
            }
        }
    }
}

double CCamera::getMoveSpeed() {
    return clock->getSeconds() * 8.0;
}

double CCamera::getRotationSpeed() {
    return clock->getSeconds() * 5.0;
}

void CCamera::drawEntity() {

}