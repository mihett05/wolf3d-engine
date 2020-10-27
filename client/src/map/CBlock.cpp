#include "CBlock.h"

CBlock::CBlock(int textureId) {
	this->textureId = textureId;
}

CBlock CBlock::eagle(1);
CBlock CBlock::redBrick(2);
CBlock CBlock::purpleStone(3);
CBlock CBlock::greyStone(4);
CBlock CBlock::blueStone(5);
CBlock CBlock::mossy(6);
CBlock CBlock::wood(7);
CBlock CBlock::colorStone(8);

map<char, CBlock> CBlock::map = { {'1', CBlock::eagle}, {'2', CBlock::redBrick}, {'3', CBlock::purpleStone}, {'4', CBlock::greyStone}, {'5', CBlock::blueStone}, {'6', CBlock::mossy}, {'7', CBlock::wood}, {'8', CBlock::colorStone},
};