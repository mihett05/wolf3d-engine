#include "CBlock.h"

char CBlock::blocks[] = {
    '1', '2', '3', '4', '5', '6', '7', '8'
};

map<char, CBlock*> CBlock::objects = map<char, CBlock*>();

CBlock::CBlock(char sign) {
	texture = sign;
}

bool CBlock::isBlock(char sign) {
    return find(blocks, blocks + sizeof(blocks), sign) != blocks + sizeof(blocks);
}

CBlock* CBlock::getBlockBySign(char sign) {
    if (objects.find(sign) == objects.end()) {
        objects[sign] = new CBlock(sign);
    }
    return objects[sign];
}

char CBlock::getTexture() {
    return texture;
}
