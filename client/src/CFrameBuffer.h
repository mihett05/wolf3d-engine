#ifndef WOLF3D_CFRAMEBUFFER_H
#define WOLF3D_CFRAMEBUFFER_H

#include <cstdint>
#include <cstdlib>

#include "Vector.h"


class CFrameBuffer {
private:
    uint32_t* buffer;
public:
    size_t w, h;

    CFrameBuffer(size_t w, size_t h);
    CFrameBuffer(size_t w, size_t h, uint32_t color);
    ~CFrameBuffer();

    void* getData();
    void clear(uint32_t color);
    void setPixel(Vector2u pos, uint32_t color);
    void drawRect(Vector2u start, Vector2u size, uint32_t color);

    static uint32_t rgbToArgb(uint8_t r, uint8_t g, uint8_t b, uint8_t a);
};


#endif //WOLF3D_CFRAMEBUFFER_H
