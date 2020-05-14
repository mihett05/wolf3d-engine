#pragma once
#include <map>
#include <SFML/Graphics.hpp>

using namespace sf;
using namespace std;

class Block
{
public:
	int textureId;
	Block() = default;
	Block(int textureId);
	static Block eagle;
	static Block redBrick;
	static Block purpleStone;
	static Block greyStone;
	static Block blueStone;
	static Block mossy;
	static Block wood;
	static Block colorStone;
	static map<char, Block> map;
};

