#include "Vector2D.h"

#define PI 3.14159265358

// 给Vector设置新的x，y
void Vector2D::set(float i, float o)
{
    x = i;
    y = o;
}

// 向量相加
void Vector2D::addVector(Vector2D v)
{
    x += v.x;
    y += v.y;
}

// 向量相减
void Vector2D::subVector(Vector2D v)
{
    x -= v.x;
    y -= v.y;
}

// 两个向量相减，并返回第一个向量的拷贝
Vector2D Vector2D::subTwoVector(Vector2D v, Vector2D v2)
{
    Vector2D tmp;
    v.x -= v2.x;
    v.y -= v2.y;
    tmp.set(v.x, v.y);
    return tmp;
}

// 向量乘法
void Vector2D::mulVector(Vector2D v)
{
    x *= v.x;
    y *= v.y;
}

// 向量乘以一个系数
void Vector2D::mulScalar(float s)
{
    x *= s;
    y *= s;
}

// 向量除法
void Vector2D::divVector(Vector2D v)
{
    x /= v.x;
    y /= v.y;
}

// 向量除以一个系数
void Vector2D::divScalar(float s)
{
    x /= s;
    y /= s;
}

// 计算两个智能体之间的距离
float Vector2D::distance(Vector2D v)
{
    float dx = x - v.x;
    float dy = y - v.y;
    float dist = sqrt(dx*dx + dy*dy);
    return dist;
}

// 限制最高飞行速度
void Vector2D::limit(float max)
{
    double size = magnitude();

    if (size > max) set(x / size, y / size);
}

//------------------------- Normalize ------------------------------------
// 二维向量标准化，即转化为长度为1的单位向量
void Vector2D::normalize()
{
    float m = magnitude();

    if (m > std::numeric_limits<double>::epsilon()) {
        set(x / m, y / m);
    } else {
        set(x, y);
    }
}
// 计算向量的模
float Vector2D::magnitude()
{
    return sqrt(x*x + y*y);
}


