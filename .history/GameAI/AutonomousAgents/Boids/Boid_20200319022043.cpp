#include <iostream>
#include <vector>
#include <string>
#include <math.h>
#include <random>
#include <ctime>
#include "Boid.h"

using namespace std;

#define PI 3.14159265358
#define	RAND_MAX 0x7fffffff

Boid::Boid(float x, float y)
{
    acceleration = Vector2D(0, 0);
    velocity = Vector2D(rand()%3 - 2, rand()%3 - 2);
    location = Vector2D(x, y);
    this->maxSpeed = 3.5;
    this->maxForce = 0.5;

    // 圆半径
    wanderRadius = 30.f;
    // 圆离boid距离
    wanderDistance = 10.f;
    // 目标点随机抖动值
    wanderJitter = 5.f;
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
    Vector2D coh = wander();
    // Arbitrarily weight these forces
    coh.mulScalar(1.0);
    // Add the force vectors to acceleration
    applyForce(coh);
}

// 更新boid位置
void Boid::update()
{
    //To make the slow down not as abrupt
    acceleration.mulScalar(.4);
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

// Adds force Pvector to current force Pvector
void Boid::applyForce(Vector2D force)
{
    acceleration.addVector(force);
}

// 控制boid随机徘徊
Vector2D Boid::wander()
{
    default_random_engine e(time(0));
    uniform_real_distribution<float> u(-1.0, 1.0);

    // // 圆半径
    // float wanderRadius = 30.f;
    // // 圆离boid距离
    // float wanderDistance = 10.f;
    // // 目标点随机抖动值
    // float wanderJitter = 5.f;

    // 1.对目标添加随机位移
    std::cout << wanderDistance << std::endl;
    float theta = (rand())/(RAND_MAX+1.0) * PI * 2;
    Vector2D wanderTarget = Vector2D(wanderRadius * cos(theta),
                              wanderRadius * sin(theta));

    //Vector2D wanderTarget = Vector2D(u(e) * wanderJitter, u(e) * wanderJitter);
    Vector2D jitter = Vector2D(u(e) * wanderJitter, u(e) * wanderJitter);
    wanderTarget.x += jitter.x;
    wanderTarget.y += jitter.y;
    // 2.对目标标准化后，重新投影到圆边上
    wanderTarget.normalize();
    wanderTarget.x *= wanderRadius;
    wanderTarget.y *= wanderRadius;
    // 3.向前移动目标
    wanderTarget.x += wanderDistance;
    // 4.计算出智能体到达目标位置的力
    location.x += wanderTarget.x;
    location.y += wanderTarget.y;

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
    acceleration.subTwoVector(desired, velocity);
    // 限制力不要超过最大力
    acceleration.limit(maxForce);

    return acceleration;
}