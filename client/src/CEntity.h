#ifndef WOLF3D_CENTITY_H
#define WOLF3D_CENTITY_H

#include <SFML/Graphics.hpp>

using namespace std;
using namespace sf;

class CEntity {
protected:
	float x, y;
	bool isSolid;
public:
	int textureId;
	CEntity() = default;
	CEntity(int textureId, float x, float y, bool isSolid);
	void setPos(Vector2f pos);
	Vector2i getRoundedPos();
	Vector2f getPos();
	bool getIsSolid();
	static CEntity* getByChar(char c, float x, float y);
};

#endif