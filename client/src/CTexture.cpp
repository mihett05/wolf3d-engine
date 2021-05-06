#include "CTexture.h"

map<char, string> CTexture::signs = map<char, string>();
map<char, vector<uint32_t>*> CTexture::textures = map<char, vector<uint32_t>*>();

vector<uint32_t>* CTexture::getTexture(char sign) {
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
    map<char, SDL_Surface*> images;


    for (auto& sign : signs) {
        SDL_RWops* rwop = SDL_RWFromFile(sign.second.c_str(), "rb");
        SDL_Surface* rawImage = IMG_LoadPNG_RW(rwop);
        SDL_RWclose(rwop);

        SDL_Surface* img = SDL_ConvertSurfaceFormat(rawImage, SDL_PIXELFORMAT_ABGR8888, 0);
        SDL_FreeSurface(rawImage);

        images[sign.first] = img;
        textures[sign.first] = new vector<uint32_t>(texWidth * texHeight);
    }

    for (int x = 0; x < texWidth; x++) {
        for (int y = 0; y < texHeight; y++) {
            for (auto& img : images) {
                (*textures[img.first])[texWidth * y + x] = getPixel(img.second, x, y);
            }
        }
    }

    for (auto& img : images) {
        SDL_FreeSurface(img.second);
    }
}

uint32_t CTexture::getPixel(SDL_Surface *surface, uint32_t x, uint32_t y) {
    size_t bytesPerPixel = surface->format->BytesPerPixel;
    uint8_t* pixel = (uint8_t*)surface->pixels + y * surface->pitch + x * bytesPerPixel;
    switch (bytesPerPixel) {
        case 1:
            return *pixel;
        case 2:
            return *(uint16_t*)pixel;
        case 3:
            if (SDL_BYTEORDER == SDL_BIG_ENDIAN)
                return pixel[0] << 16 | pixel[1] << 8 | pixel[2];
            else
                return pixel[0] | pixel[1] << 8 | pixel[2] << 16;
        case 4:
            return *(uint32_t*)pixel;
        default:
            return 0;
    }
}
