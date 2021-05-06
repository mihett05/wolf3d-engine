#ifndef WOLF3D_CCLOCK_H
#define WOLF3D_CCLOCK_H

#include <cstdint>
#include <SDL2/SDL.h>

class CClock {
private:
    uint32_t lastFrameTime;
public:
    CClock();
    uint32_t getMilliseconds() const;
    double getSeconds() const;
    void restart();
};


#endif //WOLF3D_CCLOCK_H
