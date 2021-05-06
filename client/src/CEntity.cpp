#include "CEntity.h"

char CEntity::entities[] = {
    'l'
};

map<uint32_t, SEntityType*> entityTypes = {
    {0, new SEntityType('l', true)},
};

CEntity::CEntity(uint32_t uid, uint32_t entityType, float x, float y) {
    this->uid = uid;
	this->entityType = entityType;
	this->x = x;
	this->y = y;
}


void CEntity::setPos(Vector2f pos) {
	x = pos.x;
	y = pos.y;
}

bool CEntity::isEntity(char c) {

    return find(entities, entities + sizeof(entities), c) != entities + sizeof(entities);
}

CEntity* CEntity::getByChar(char c, float x, float y) {
	CEntity* ent = nullptr;
    // uid = 0 - only in SinglePlayer
	switch (c) {
        case 'l':
            ent = new CEntity(0, 0, x, y);
            break;
        default:
            break;
	}
	return ent;
}

Vector2i CEntity::getRoundedPos() const {
	return {int(x), int(y)};
}

Vector2f CEntity::getPos() const {
	return {x, y};
}

char CEntity::getTexture() const {
    return entityTypes[entityType]->texture;
}

bool CEntity::getIsSolid() const {
	return entityTypes[entityType]->isSolid;
}




