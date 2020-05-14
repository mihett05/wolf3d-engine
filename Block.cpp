#include "Block.h"

Block::Block(int textureId)
{
	this->textureId = textureId;
}

Block Block::eagle(1);
Block Block::redBrick(2);
Block Block::purpleStone(3);
Block Block::greyStone(4);
Block Block::blueStone(5);
Block Block::mossy(6);
Block Block::wood(7);
Block Block::colorStone(8);

map<char, Block> Block::map = {
	{'1', Block::eagle},
	{'2', Block::redBrick},
	{'3', Block::purpleStone},
	{'4', Block::greyStone},
	{'5', Block::blueStone},
	{'6', Block::mossy},
	{'7', Block::wood},
	{'8', Block::colorStone},
};