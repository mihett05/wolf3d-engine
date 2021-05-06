#ifndef WOLF3D_CTEXTURE_H
#define WOLF3D_CTEXTURE_H

#include <vector>
#include <map>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#define texWidth 64
#define texHeight 64

using namespace std;


class CTexture {
private:
    static map<char, string> signs;
    static map<char, vector<uint32_t>*> textures;
public:
    static vector<uint32_t>* getTexture(char sign);

    static void setSign(char sign, const string& file);
    static void initSigns();
    static void loadFiles();

    static uint32_t getPixel(SDL_Surface* surface, uint32_t x, uint32_t y);
};

#endif //WOLF3D_CTEXTURE_H
