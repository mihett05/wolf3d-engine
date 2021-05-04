#define _USE_MATH_DEFINES

#include <chrono>
#include <functional>
#include <vector>
#include <SFML/System.hpp>

#include "CGame.h"

CGame::CGame(unsigned int width, unsigned int height, const string& title, unsigned int frameLimit) {
	window = make_unique<RenderWindow>(VideoMode(width, height), title);
	window->setFramerateLimit(frameLimit);
	map = new CMap("maps/level_1.txt");
	clock = new Clock();
	
	camera = new CCamera(clock, window->getSize().x, window->getSize().y, map);
}


void CGame::draw() {
	window->clear(Color(84, 84, 84));
	window->draw(*camera->draw());
	window->display();
}

void CGame::update() {
	clock->restart();
	draw();
}

void CGame::loop() {
	while (window->isOpen()) {
		while (window->pollEvent(this->event)) {
			if (event.type == sf::Event::Closed || event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
				window->close();
		}
		update();
	}

}

void CGame::destroy() {

}