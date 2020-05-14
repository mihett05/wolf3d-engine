#include "Entity.h"

Entity::Entity(Sprite sprite)
{
	this->sprite = sprite;
}


void Entity::setPosition(Vector2f pos)
{
	x = pos.x;
	y = pos.y;
}
