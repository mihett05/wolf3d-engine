#define _USE_MATH_DEFINES

#include <functional>
#include <vector>

#include "CGame.h"

CGame::CGame(int width, int height, const string& title, unsigned int frameLimit) {
	window = SDL_CreateWindow(title.c_str(), 100, 100, width, height, SDL_WINDOW_SHOWN | SDL_WINDOW_INPUT_FOCUS);
	map = new CMap("maps/level_1.txt");
	clock = new CClock();

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

	SDL_GetWindowSize(window, &w, &h);
	buffer = new CFrameBuffer(width, height);
	camera = new CCamera(buffer, clock, map);
    bufferTexture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ABGR8888, SDL_TEXTUREACCESS_STREAMING, w, h);
}


void CGame::draw() {
    camera->draw();
    SDL_UpdateTexture(bufferTexture, NULL, buffer->getData(), buffer->w * 4);

    SDL_SetRenderDrawColor(renderer, 84, 84, 84, 0xFF);
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, bufferTexture, NULL, NULL);
	SDL_RenderPresent(renderer);
}

void CGame::update() {
	clock->restart();
	draw();
}

void CGame::loop() {
    bool quit = false;
    while (!quit) {
        while (SDL_PollEvent(&event) != 0) {
            if (event.type == SDL_QUIT || event.type == SDL_KEYDOWN && event.key.keysym.scancode == SDL_SCANCODE_ESCAPE) {
                quit = true;
            }
        }
        update();
    }
    destroy();
}

void CGame::destroy() {
    delete buffer;
    delete clock;
    delete map;
    SDL_DestroyTexture(bufferTexture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
}