#define _USE_MATH_DEFINES

#include <math.h>
#include <iostream>
#include <functional>
#include <vector>
#include <SFML/System.hpp>

#include "CGame.h"

CGame::CGame(unsigned int width, unsigned int height, string title, unsigned int frameLimit) {
	window = make_unique<RenderWindow>(VideoMode(width, height), title);
	window->setFramerateLimit(frameLimit);
	map = new CMap("maps/level_1.txt");
	clock = new Clock();
	
	camera = new CCamera(clock, window->getSize().x, window->getSize().y, map);
}


void CGame::draw() {
	window->clear(Color(84, 84, 84));
	
	VertexArray buffer = camera->draw();
	window->draw(buffer);
	window->display();
}

void CGame::update() {
	/*if (Keyboard::isKeyPressed(Keyboard::A) || Keyboard::isKeyPressed(Keyboard::D)) {
		if (Keyboard::isKeyPressed(Keyboard::A))
			player.rotate(-1 * clock.getElapsedTime().asSeconds());
		if (Keyboard::isKeyPressed(Keyboard::D))
			player.rotate(1 * clock.getElapsedTime().asSeconds());

	}*/
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