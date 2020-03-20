#ifndef BOID_H
#define BOID_H
#include <iostream>
#include <vector>
#include <stdlib.h>
#include <ctime>
#include <random>
#include <string>
#include <math.h>
#include <SFML/System.hpp>
#include "Vector2D.h"
#include "C2DMatrix.h"

// -----------------------The Boid Class------------------------
// 属性：
// location: boid的位置向量
// velocity: boid的速度向量
// acceleration: boid的当前加速度
// maxSpeed: 速度矢量极限值
// maxForce: 加速度矢量极限值
// elapsed: 当前时刻和上一时刻的差值
// wanderRadius: 圆半径
// wanderDistance: 目标移动距离
// wanderJitter: 目标点随机抖动值
// wanderTarget: 存储目标点
//
// 方法：
// run(): boid开始活动
// separation(): 领域内若有其他boids存在，该函数计算出一个距离，
//              使当前boid与其他boids保持距离.
// alignment(): 该函数计算出一个速度矢量，使其与其他boids保持相同的速度.
//             并维持队列。
// cohesion(): 计算出附近boids的质心，并使当前boid前往该质心
// ---------------------------------------------------------------

class Boid
{
private:
    float maxSpeed;
    float maxForce;
    int winWidth;
    int winHeight;

    double elapsed;

    float wanderRadius;
    float wanderDistance;
    float wanderJitter;
    Vector2D wanderTarget;

public:
    Boid() {}
    ~Boid() {}
    Boid(float x, float y);

    Vector2D location;
    Vector2D velocity;
    Vector2D acceleration;
    // The Steering Behavior
    Vector2D separation(std::vector<Boid> boids);
    Vector2D alignment(std::vector<Boid> boids);
    Vector2D cohesion(std::vector<Boid> boids);

    void steeringBehavior();
    Vector2D seek(Vector2D v);
    Vector2D wander();

    void run();
    void setWindow(int width, int height);
    void setElapsed(double e);
    void update();
    void isOutBorders();
    void applyForce(Vector2D force);
};

#endif