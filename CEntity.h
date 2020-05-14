#pragma once
#include <SFML/Graphics.hpp>

using namespace std;
using namespace sf;

class CEntity
{
public:
	Sprite sprite;
	float x, y;
	CEntity() = default;
	CEntity(Sprite sprite);
	void setPosition(Vector2f pos);
};

