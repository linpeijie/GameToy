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

// Creates and returns a copy of the Pvector used as a parameter
Vector2D Vector2D::copy(Pvector v)
{
    Pvector copy(v.x, v.y);
    return copy;
}