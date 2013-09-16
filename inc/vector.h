#ifndef VECTOR_H
#define VECTOR_H

//! @brief Vector2d structure for 2-value double vectors, positions, etc.
struct Vector2d
{
    Vector2d(double x0, double y0) {
        x = x0;
        y = y0;
    }

    Vector2d() {
        x = y = 0.0;
    }

    double x;
    double y;
};

//! @brief Vector2i structure for 2-value integer vectors, positions, etc.
struct Vector2i
{
    Vector2i(int x0, int y0 ) {
        x = x0;
        y = y0;
    }

    Vector2i() {
        x = y = 0;
    }

    int x;
    int y;
};



#endif

