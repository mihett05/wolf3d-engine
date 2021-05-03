#ifndef WOLF3D_CTEXTURE_H
#define WOLF3D_CTEXTURE_H

#include <vector>
#include <map>
#include <SFML/Graphics.hpp>

#define texWidth 64
#define texHeight 64

using namespace std;
using namespace sf;

class CTexture {
private:
    static map<char, string> signs;
    static map<char, vector<Uint32>*> textures;
public:
    static vector<Uint32>* getTexture(char sign);
    static void setSign(char sign, const string& file);
    static void initSigns();
    static void loadFiles();

};

#endif //WOLF3D_CTEXTURE_H
