#ifndef VECTOR2D_H
#define VECTOR2D_H

#include <iostream>
#include <math.h>

class Vector2D
{

public:
    float x;
    float y;

    Vector2D() {}
    Vector2D(float xComp, float yComp)
    {
        x = xComp;
        y = yComp;
    }
};

#endif