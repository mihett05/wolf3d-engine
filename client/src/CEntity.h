#ifndef WOLF3D_CENTITY_H
#define WOLF3D_CENTITY_H

#include <SFML/Graphics.hpp>

#include "CTexture.h"

using namespace std;
using namespace sf;

struct SEntityType {
    char texture;
    bool isSolid;
    SEntityType(char texture, bool isSolid) {
        this->texture = texture;
        this->isSolid = isSolid;
    }
};


class CEntity {
private:
    static char entities[];
protected:
    int entityType;
    uint32_t uid;
	float x, y;
public:
	CEntity() = default;
	CEntity(uint32_t uid, uint32_t entityType, float x, float y);
	void setPos(Vector2f pos);
	Vector2i getRoundedPos() const;
	Vector2f getPos() const;

	char getTexture() const;
	bool getIsSolid() const;

	static bool isEntity(char c);
	static CEntity* getByChar(char c, float x, float y);
};

#endif