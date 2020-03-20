#include "Vector2D.h"

#define PI 3.14159265358

// Sets values of x and y for Pvector
void Vector2D::set(float i, float o)
{
    x = i;
    y = o;
}

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
void Vector2D::limit(float max)
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

// normalize divides x and y by magnitude if it has a magnitude.
void Vector2D::normalize()
{
    float m = magnitude();
    // 若大于自然数,则执行归一化
    if (m > std::numeric_limits<double>::epsilon()) {
        set(x / m, y / m);
    } else {
        set(x, y);
    }
}
