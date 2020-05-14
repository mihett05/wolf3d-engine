#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;
using namespace std;

class Player
{
public:
	float x, y, angle;
	Player();
	void rotate(float angle);
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

