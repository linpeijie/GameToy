#ifndef VECTOR2D_H
#define VECTOR2D_H

#include <iostream>
#include <math.h>

class Vector2D
{

public:
    const float x;
    const float y;

    Vector2D() {}
    Vector2D(float xComp, float yComp)
    {
        x = xComp;
        y = yComp;
    }

    void set(float i, float o);
    // 标量函数 通过float浮点数来缩放 向量
    void addVector(Vector2D v);

    void mulVector(Vector2D v);
    void mulScalar(float x);

    void limit(float max);

    float magnitude();
};

#endif