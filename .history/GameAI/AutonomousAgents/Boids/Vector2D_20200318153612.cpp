#include "Vector2D.h"

#define PI 3.14159265358

void Vector2D::addVector(Vector2D v)
{
    x += v.x;
    y += v.y;
}

void Vector2D::mulVector(Vector2D v)
{
    x *= v.x;
    y *= v.y;
}

void Vector2D::mulScalar(float s)
{
    x *= s;
    y *= s;
}

// 限制最高飞行速度
void Vector2D::limit(double max)
{
    double size = magnitude();

    if (size > max) {
        set(x / size, y / size);
    }
}

// Calculates magnitude of referenced object
float Vector2D::magnitude()
{
    return sqrt(x*x + y*y);
}