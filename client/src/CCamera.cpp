#include <iostream>
#include "CCamera.h"
#include "CTexture.h"

#define texWidth 64
#define texHeight 64

CCamera::CCamera(Clock* clock, int width, int height, CMap* map) {
	this->clock = clock;
	this->screenWidth = width;
	this->screenHeight = height;
	this->map = map;

    pixels = new VertexArray(Points, screenWidth * screenHeight);

	posX = map->spawnPosition.x + 0.5;
	posY = map->spawnPosition.y + 0.5;
	dirX = -1.0;
	dirY = 0.0;
	planeX = 0.0;
	planeY = 0.66;

    CTexture::initSigns();
    CTexture::loadFiles();
}

VertexArray* CCamera::draw() {
    pixels->clear();
	
	for (int x = 0; x < screenWidth; x++) {
		double cameraX = (double)(2 * x) / (double)screenWidth - 1;
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

		int lineHeight = (int)(screenHeight / perpWallDist);

		int drawStart = -lineHeight / 2 + screenHeight / 2;
		if (drawStart < 0) drawStart = 0;
		int drawEnd = lineHeight / 2 + screenHeight / 2;
		if (drawEnd >= screenHeight) drawEnd = screenHeight - 1;
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
		double texPos = (drawStart - screenHeight / 2 + lineHeight / 2) * step;

		vector<Uint32>* texture = CTexture::getTexture(textureSign);
		for (int y = drawStart; y < drawEnd; y++) {
			int texY = (int)texPos & (texHeight - 1);
			texPos += step;
			Uint32 color = texture->at(texHeight * texY + texX);
			//if (side == 1) color = (color >> 1) & 8355711;
			Vertex ver;
			ver.position = Vector2f(x, y);
			ver.color = Color(color);
			pixels->append(ver);
		}
	}

    for (uint32_t i = 0; i < map->entities->size(); ++i) {

    }

	double moveSpeed = getMoveSpeed(); //the constant value is in squares/second
	double rotSpeed = getRotationSpeed(); //the constant value is in radians/second

	if (Keyboard::isKeyPressed(Keyboard::W)) {
		moveStraight(true, moveSpeed);
	}
	if (Keyboard::isKeyPressed(Keyboard::S)) {
        moveStraight(false, moveSpeed);
	}
	if (Keyboard::isKeyPressed(Keyboard::D)) {
		double oldDirX = dirX;
		dirX = dirX * cos(-rotSpeed) - dirY * sin(-rotSpeed);
		dirY = oldDirX * sin(-rotSpeed) + dirY * cos(-rotSpeed);
		double oldPlaneX = planeX;
		planeX = planeX * cos(-rotSpeed) - planeY * sin(-rotSpeed);
		planeY = oldPlaneX * sin(-rotSpeed) + planeY * cos(-rotSpeed);
	}
	if (Keyboard::isKeyPressed(Keyboard::A)) {
		double oldDirX = dirX;
		dirX = dirX * cos(rotSpeed) - dirY * sin(rotSpeed);
		dirY = oldDirX * sin(rotSpeed) + dirY * cos(rotSpeed);
		double oldPlaneX = planeX;
		planeX = planeX * cos(rotSpeed) - planeY * sin(rotSpeed);
		planeY = oldPlaneX * sin(rotSpeed) + planeY * cos(rotSpeed);
	}
	return pixels;
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
    return clock->getElapsedTime().asSeconds() * 8.0;
}

double CCamera::getRotationSpeed() {
    return clock->getElapsedTime().asSeconds() * 5.0;
}

void CCamera::drawEntity() {

}


