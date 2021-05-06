#pragma once
#include <string>
#include <vector>
#include <SDL2/SDL.h>

#include "CClock.h"
#include "CEntity.h"
#include "CCamera.h"
#include "./map/CMap.h"

#define mapWidth 24
#define mapHeight 24

using namespace std;

class CGame {
protected:
	SDL_Window* window;
	SDL_Renderer* renderer;
	SDL_Event event;

	SDL_Texture* bufferTexture;

	int w, h;
	CClock* clock;
	CCamera* camera;
	CMap* map;
	
public:
	CGame(int width, int height, const string& title, unsigned int frameLimit);
	void draw();
	void update();
	void loop();
	void destroy();
};

