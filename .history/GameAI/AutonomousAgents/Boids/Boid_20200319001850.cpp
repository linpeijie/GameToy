#include <iostream>
#include <vector>
#include <string>
#include <math.h>
#include <random>
#include <ctime>
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
    default_random_engine e(time(0));
    uniform_real_distribution<float> u(-1.0, 1.0);

    // 圆半径
    float wanderRadius = 6.f;
    // 圆离boid距离
    float wanderDistance = 3.f;
    // 目标点随机抖动值
    float wanderJitter = 2.f;

    // 1.对目标添加随机位移
    Vector2D wanderTarget = Vector2D(u(e) * wanderJitter, u(e) * wanderJitter);
    // 2.对目标标准化后，重新投影到圆边上
    wanderTarget.normalize();
    wanderTarget.x *= wanderRadius;
    wanderTarget.y *= wanderRadius;
    // 3.向前移动目标
    wanderTarget.x += wanderDistance;
    // 4.计算出智能体到达目标位置的力
    seek(wanderTarget);
}

// 返回一个智能体到达目标的力
Vector2D Boid::seek(Vector2D v)
{
    Vector2D desired;
    desired.subVector(v);  // A vector pointing from the location to the target
    // Normalize desired and scale to maximum speed
    desired.normalize();
    desired.mulScalar(maxSpeed);
    // Steering = Desired minus Velocity
    acceleration.subTwoVector(desired, velocity);
    acceleration.limit(maxForce);  // Limit to maximum steering force
    return acceleration;
}