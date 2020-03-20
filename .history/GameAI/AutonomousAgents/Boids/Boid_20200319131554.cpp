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

    // 初始化wanderTarget位置
    wanderRadius = 6.f;
    wanderDistance = 1.f;
    wanderJitter = 2.f;

    default_random_engine e(time(0));
    uniform_real_distribution<float> m(0, INT_MAX);
    float theta = (m(e)/(INT_MAX)) * 360;
    float t = (m(e)/(INT_MAX)) * 360;
    wanderTarget = Vector2D(wanderRadius * cos(theta), wanderRadius * sin(theta));
    cout << theta << endl;
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
    //steeringBehavior();
    wander();
    //update();
    isOutBorders();
}

// Applies the three laws to the flock of boids
void Boid::steeringBehavior()
{
    Vector2D wan = wander();
    // Arbitrarily weight these forces
    wan.mulScalar(1.0);
    // Add the force vectors to acceleration
    applyForce(wan);
}

// 更新boid位置
void Boid::update()
{
    //To make the slow down not as abrupt
    acceleration.mulScalar(.2);
    // Update velocity
    velocity.addVector(acceleration);
    // Limit speed
    velocity.limit(maxSpeed);
    location.addVector(velocity);
    // Reset accelertion to 0 each cycle
    acceleration.mulScalar(0);
}

// 当boid飞出窗口，校正其位置
void Boid::isOutBorders()
{
    if (location.x < 0) location.x += winWidth;
    if (location.y < 0) location.y += winHeight;
    if (location.x > winWidth) location.x -= winWidth;
    if (location.y > winHeight) location.y -= winHeight;
}

// 将计算出来的力与当前力相加，改变boid运动方向
void Boid::applyForce(Vector2D force)
{
    acceleration.addVector(force);
}

// 控制boid随机徘徊
Vector2D Boid::wander()
{
    default_random_engine e(time(0));
    uniform_real_distribution<float> u(-1.0, 1.0);

    // 1.对目标添加随机位移
    wanderTarget.subVector(Vector2D(u(e) * wanderJitter, u(e) * wanderJitter));
    // 2.对目标标准化后，重新投影到圆边上
    wanderTarget.normalize();
    wanderTarget.mulScalar(wanderRadius);
    // 3.向前移动目标
    wanderTarget.addVector(Vector2D(wanderDistance, 0));
    // 4.把目标投影到世界空间
    //wanderTarget.addVector(location);
    wanderTarget.mulScalar(0.1);
    location.addVector(wanderTarget);
    // 4.计算出智能体到达目标位置的力
    //return seek(wanderTarget);
    return wanderTarget;
}

// 返回一个智能体到达目标的 力
Vector2D Boid::seek(Vector2D v)
{
    Vector2D desired;
    // 1.计算预期速度，该速度从boid位置指向目标位置
    //  理想化速度，即为boid移动的最大速度
    desired.subVector(v);
    desired.normalize();
    desired.mulScalar(maxSpeed);
    // 移动所需的速度 = 预期速度 - 当前速度
    Vector2D res = acceleration.subTwoVector(desired, velocity);
    // 限制力不要超过最大力
    res.limit(maxForce);

    return res;
}