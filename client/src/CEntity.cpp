#include "CEntity.h"

CEntity::CEntity(int textureId, float x, float y, bool isSolid) {
	this->textureId = textureId;
}


void CEntity::setPos(Vector2f pos) {
	x = pos.x;
	y = pos.y;
}

CEntity* CEntity::getByChar(char c, float x, float y) {
	CEntity* ent = nullptr;

	switch (c) {
	case 'l':
		ent = new CEntity(8, x, y, false);
		break;
	default:
		break;
	}
	return ent;

}

Vector2i CEntity::getRoundedPos() {
	return Vector2i(int(x), int(y));
}

Vector2f CEntity::getPos() {
	return Vector2f(x, y);
}

bool CEntity::getIsSolid() {
	return isSolid;
}