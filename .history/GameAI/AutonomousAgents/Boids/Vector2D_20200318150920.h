#ifndef VECTOR2D_H
#define VECTOR2D_H

#include <iostream>

class Vector2D
{
private:
    float x;
    float y;

public:
    Vector2D() {}
    Vector2D(float xComp, float yComp)
    {
        x = xComp;
        y = yComp;
    }

    // 标量函数 通过float浮点数来缩放 向量
    void addVector(Vector2D v);

    void mulVector(Vector2D v);
    void mulScalar(float x);

    void limit(float max);


};

#endif