#include <iostream>
#include "CCamera.h"
#define texWidth 64
#define texHeight 64

CCamera::CCamera(Clock* clock, int width, int height, CMap* map) {
	this->clock = clock;
	this->screenWidth = width;
	this->screenHeight = height;
	this->map = map;

	posX = map->spawnPosition.x + 0.5;
	posY = map->spawnPosition.y + 0.5;
	dirX = -1.0;
	dirY = 0.0;
	planeX = 0.0;
	planeY = 0.66;
	
	for (auto& i : texture) i.resize(texWidth * texHeight);

	Image eagle, redbrick, purplestone, greystone, bluestone, mossy, wood, colorstone, lamp;
	eagle.loadFromFile("media/eagle.png");
	redbrick.loadFromFile("media/redbrick.png");
	purplestone.loadFromFile("media/purplestone.png");
	greystone.loadFromFile("media/greystone.png");
	bluestone.loadFromFile("media/bluestone.png");
	mossy.loadFromFile("media/mossy.png");
	wood.loadFromFile("media/wood.png");
	colorstone.loadFromFile("media/colorstone.png");
	lamp.loadFromFile("media/eLamp.png");

	for (int x = 0; x < texWidth; x++)
		for (int y = 0; y < texHeight; y++) {
			texture[0][texWidth * y + x] = eagle.getPixel(x, y).toInteger();
			texture[1][texWidth * y + x] = redbrick.getPixel(x, y).toInteger();
			texture[2][texWidth * y + x] = purplestone.getPixel(x, y).toInteger();
			texture[3][texWidth * y + x] = greystone.getPixel(x, y).toInteger();
			texture[4][texWidth * y + x] = bluestone.getPixel(x, y).toInteger();
			texture[5][texWidth * y + x] = mossy.getPixel(x, y).toInteger();
			texture[6][texWidth * y + x] = wood.getPixel(x, y).toInteger();
			texture[7][texWidth * y + x] = colorstone.getPixel(x, y).toInteger();
			texture[8][texWidth * y + x] = lamp.getPixel(x, y).toInteger();
		}

}

VertexArray CCamera::draw() {
	VertexArray pixels(Points, screenWidth * screenHeight);
	
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

		bool isEntity = false;
		CEntity* ent = nullptr;

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
			ent = map->getEntityOn(mapX, mapY);
			if (map->map[mapX][mapY]->type != EMPTY)
				hit = true;
			else if (ent != nullptr) {
				cout << ent->textureId << endl;
				hit = true;
				isEntity = true;
			}
		}

		if (side == 0) perpWallDist = (mapX - posX + (1 - stepX) / 2) / rayDirX;
		else perpWallDist = (mapY - posY + (1 - stepY) / 2) / rayDirY;

		int lineHeight = (int)(screenHeight / perpWallDist);

		int drawStart = -lineHeight / 2 + screenHeight / 2;
		if (drawStart < 0) drawStart = 0;
		int drawEnd = lineHeight / 2 + screenHeight / 2;
		if (drawEnd >= screenHeight) drawEnd = screenHeight - 1;
		int texNum = 0;
		
		if (map->map[mapX][mapY]->type == BLOCK) {
			texNum = map->map[mapX][mapY]->block.textureId;
		}
		else if (isEntity)
			texNum = ent->textureId;
		else
			continue;
		

		double wallX;
		if (side == 0) wallX = posY + perpWallDist * rayDirY;
		else wallX = posX + perpWallDist * rayDirX;
		wallX -= floor((wallX));

		int texX = int(wallX * double(texWidth));
		if (side == 0 && rayDirX > 0) texX = texWidth - texX - 1;
		if (side == 1 && rayDirY < 0) texX = texWidth - texX - 1;

		double step = 1.0 * texHeight / lineHeight;
		double texPos = (drawStart - screenHeight / 2 + lineHeight / 2) * step;
		for (int y = drawStart; y < drawEnd; y++) {
			int texY = (int)texPos & (texHeight - 1);
			texPos += step;
			Uint32 color = texture[texNum][texHeight * texY + texX];
			//if (side == 1) color = (color >> 1) & 8355711;
			Vertex ver;
			ver.position = Vector2f(x, y);
			ver.color = Color(color);
			pixels.append(ver);
		}
	}
	double moveSpeed = clock->getElapsedTime().asSeconds() * 5.0; //the constant value is in squares/second
	double rotSpeed = clock->getElapsedTime().asSeconds() * 3.0; //the constant value is in radians/second

	if (Keyboard::isKeyPressed(Keyboard::W)) {
		CMapCell* cellX = map->map[int(posX + dirX * moveSpeed)][int(posY)];
		CMapCell* cellY = map->map[int(posX)][int(posY + dirY * moveSpeed)];

		CMapCell* cellNextX = map->map[int(posX + dirX * moveSpeed + (dirX >= 0 ? 1 : -1))][int(posY)];
		CMapCell* cellNextY = map->map[int(posX)][int(posY + dirY * moveSpeed + (dirY >= 0 ? 1 : -1))];
		float diffX = floorf(abs(int(posX + dirX * moveSpeed) - posX) * 10.0 + 0.5) / 10.0;
		bool canMoveX = cellX->type == EMPTY && (cellNextX->type == EMPTY || (cellNextX->type == BLOCK && ((diffX >= 0.5 && dirX < 0) || ((diffX <= 0.5 || diffX > 1) && dirX >= 0))));
		float diffY = floorf(abs(int(posY + dirY * moveSpeed) - posY) * 10.0 + 0.5) / 10.0;
		bool canMoveY = cellY->type == EMPTY && (cellNextY->type == EMPTY || (cellNextY->type == BLOCK && ((diffY >= 0.5 && dirY < 0) || ((diffY <= 0.5 || diffY > 1) && dirY >= 0))));
		if (canMoveX)
			posX += dirX * moveSpeed;
		if (canMoveY)
			posY += dirY * moveSpeed;
	}
	if (Keyboard::isKeyPressed(Keyboard::S)) {
		CMapCell* cellX = map->map[int(posX - dirX * moveSpeed)][int(posY)];
		CMapCell* cellY = map->map[int(posX)][int(posY - dirY * moveSpeed)];

		CMapCell* cellNextX = map->map[int(posX + dirX * moveSpeed + (dirX >= 0 ? -1 : 1))][int(posY)];
		CMapCell* cellNextY = map->map[int(posX)][int(posY + dirY * moveSpeed + (dirY >= 0 ? -1 : 1))];
		float diffX = floorf(abs(int(posX + dirX * moveSpeed) - posX) * 10.0 + 0.5) / 10.0;
		bool canMoveX = cellX->type == EMPTY && (cellNextX->type == EMPTY || (cellNextX->type == BLOCK && ((diffX >= 0.5 && dirX >= 0) || ((diffX <= 0.5 || diffX > 1) && dirX < 0))));
		float diffY = floorf(abs(int(posY + dirY * moveSpeed) - posY) * 10.0 + 0.5) / 10.0;
		bool canMoveY = cellY->type == EMPTY && (cellNextY->type == EMPTY || (cellNextY->type == BLOCK && ((diffY >= 0.5 && dirY >= 0) || ((diffY <= 0.5 || diffY > 1) && dirY < 0))));
		if (canMoveX && canMoveY) {
            posX -= dirX * moveSpeed;
            posY -= dirY * moveSpeed;
		}
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