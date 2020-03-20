#include <iostream>
#include <vector>
#include <string>
#include <math.h>
#include <random>
#include "Boid.h"

using namespace std;

#define PI 3.14159265358

Boid::Boid(float x, float y)
{
    acceleration = Vector2D(0, 0);
    velocity = Vector2D(rand()%3 - 2, rand()%3 - 2);
    location = Vector2D(x, y);
    this->maxSpeed = 3.5;
    this->maxForce = 0.5;
}

// 设置窗口大小
void Boid::setWindow(int width, int height)
{
    winWidth = width;
    winHeight = height;
}

// 运行三个函数，behavior、update和isOutBorders
void Boid::run()
{
    update();
    isOutBorders();
}

// 更新boid位置
void Boid::update()
{
    wander();
}

// 当boid飞出窗口，校正其位置
void Boid::isOutBorders()
{
    if (location.x < 0) location.x += winWidth;
    if (location.y < 0) location.y += winHeight;
    if (location.x > winWidth) location.x -= winWidth;
    if (location.y > winHeight) location.y -= winHeight;
}

// 控制boid随机徘徊
Vector2D Boid::wander()
{
    default_random_engine e;
    uniform_real_distribution<float> u(-1.0, 1.0);
    // 圆半径
    float wanderRadius;
    // 圆离boid距离
    float wanderDistance;
    // 目标点随机抖动值
    float wanderJitter;


}