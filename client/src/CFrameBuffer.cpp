#include "CFrameBuffer.h"

CFrameBuffer::CFrameBuffer(size_t w, size_t h) : w(w), h(h) {
    buffer = (uint32_t*)calloc(sizeof(uint32_t), w * h);
}

CFrameBuffer::CFrameBuffer(size_t w, size_t h, uint32_t color) : w(w), h(h) {
    buffer = (uint32_t*)malloc(sizeof(uint32_t) * w * h);
    clear(color);
}

CFrameBuffer::~CFrameBuffer() {
    free(buffer);
}

void* CFrameBuffer::getData() {
    return (void*)buffer;
}

void CFrameBuffer::clear(uint32_t color) {
    for (int i = 0; i < w * h; ++i) {
        buffer[i] = color;
    }
}

void CFrameBuffer::setPixel(Vector2u pos, uint32_t color) {
    if (pos.x < w && pos.y < h) {
        buffer[pos.x + pos.y * w] = color;
    }
}

void CFrameBuffer::drawRect(Vector2u start, Vector2u size, uint32_t color) {

}

uint32_t CFrameBuffer::rgbToArgb(uint8_t r, uint8_t g, uint8_t b, uint8_t a) {
    return ((a & 0xff) << 24) | ((r & 0xff) << 16) | ((g & 0xff) << 8) | ((b & 0xff));
}


