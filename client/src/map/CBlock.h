#pragma once
#include <map>
#include <SFML/Graphics.hpp>

using namespace sf;
using namespace std;

class CBlock {
public:
	int textureId;
	CBlock() = default;
	CBlock(int textureId);
	static CBlock eagle;
	static CBlock redBrick;
	static CBlock purpleStone;
	static CBlock greyStone;
	static CBlock blueStone;
	static CBlock mossy;
	static CBlock wood;
	static CBlock colorStone;
	static map<char, CBlock> map;
};

