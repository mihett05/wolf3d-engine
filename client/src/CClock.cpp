#include "CClock.h"

CClock::CClock() : lastFrameTime(SDL_GetTicks()) {}

uint32_t CClock::getMilliseconds() const {
    return SDL_GetTicks() - lastFrameTime;
}

double CClock::getSeconds() const {
    return (double)getMilliseconds() / 1000;
}

void CClock::restart() {
    lastFrameTime = SDL_GetTicks();
}
