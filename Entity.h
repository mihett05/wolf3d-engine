#pragma once
#include <SFML/Graphics.hpp>

using namespace std;
using namespace sf;

class Entity
{
public:
	Sprite sprite;
	float x, y;
	Entity() = default;
	Entity(Sprite sprite);
	void setPosition(Vector2f pos);
};

