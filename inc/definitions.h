#ifndef DEFINITIONS_H
#define DEFINITIONS_H

#include <stdio.h>

//! @brief Color structure for RGB components.
struct Color
{
    Color(double r0, double g0, double b0) {
        r = r0;
        g = g0;
        b = b0;
    }

    Color() {
        r = g = b = 0.0;
    }

    double r;
    double g;
    double b;
};

//! @brief Volume structure to encapsulate viewing volumes such as viewport.
struct Volume
{
    Volume() {
        left = 0.0;
        right = 0.0;
        top = 0.0;
        bottom = 0.0;
        near = 0.0;
        far = 0.0;
    }

    void Print( const char *s ) {
        printf("%s: L%f, R%f, B%f, T%f\n", s, left, right, bottom, top);
    }

    //! Left side of the volume.
    double left;
    //! Right side of the volume.
    double right;
    //! Bottom side of the volume.
    double bottom;
    //! Top side of the volume.
    double top;
    //! Near side of the volume.
    double near;
    //! Far side of the volume.
    double far;
};

#endif

