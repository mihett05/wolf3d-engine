#include "CTexture.h"

map<char, string> CTexture::signs = map<char, string>();
map<char, vector<Uint32>*> CTexture::textures = map<char, vector<Uint32>*>();

vector<Uint32>* CTexture::getTexture(char sign) {
    return textures[sign];
}

void CTexture::setSign(char sign, const string& file) {
    signs[sign] = file;
}

void CTexture::initSigns() {
    setSign('1', "media/eagle.png");
    setSign('2', "media/redbrick.png");
    setSign('3', "media/purplestone.png");
    setSign('4', "media/greystone.png");
    setSign('5', "media/bluestone.png");
    setSign('6', "media/mossy.png");
    setSign('7', "media/wood.png");
    setSign('8', "media/colorstone.png");
    setSign('l', "media/ent_lamp.png");
}

void CTexture::loadFiles() {
    map<char, Image*> images;

    for (auto& sign : signs) {
        Image* img = new Image();
        img->loadFromFile(sign.second);
        images[sign.first] = img;
        textures[sign.first] = new vector<Uint32>(texWidth * texHeight);
    }

    for (int x = 0; x < texWidth; x++) {
        for (int y = 0; y < texHeight; y++) {
            for (auto& img : images) {
                (*textures[img.first])[texWidth * y + x] = img.second->getPixel(x, y).toInteger();
            }
        }
    }

    for (auto& img : images) {
        delete img.second;
    }
}
