#include "CEntity.h"

CEntity::CEntity(Sprite sprite)
{
	this->sprite = sprite;
}


void CEntity::setPosition(Vector2f pos)
{
	x = pos.x;
	y = pos.y;
}
