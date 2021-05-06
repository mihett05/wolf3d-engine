#ifndef WOLF3D_VECTOR_H
#define WOLF3D_VECTOR_H

#include <cstdint>

template <typename T>
struct Vector2 {
    T x, y;

    Vector2() {
        x = 0;
        y = 0;
    }

    Vector2(T x, T y) {
        this->x = x;
        this->y = y;
    }
};

typedef Vector2<int> Vector2i;
typedef Vector2<uint32_t> Vector2u;
typedef Vector2<float> Vector2f;
typedef Vector2<double> Vector2d;


#endif //WOLF3D_VECTOR_H
