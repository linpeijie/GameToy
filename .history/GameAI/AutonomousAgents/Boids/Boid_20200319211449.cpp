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

    // 初始化wanderTarget向量
    wanderRadius = 6.f;
    wanderDistance = 1.f;
    wanderJitter = 60.f;
    wanderDisSum = 0.0;

    float theta = (rand())/(RAND_MAX+1.0) * PI * 2;
    wanderTarget = Vector2D(wanderRadius * cos(theta), wanderRadius * sin(theta));

}

// 设置窗口大小
void Boid::setWindow(int width, int height)
{
    winWidth = width;
    winHeight = height;
}

// 设置时钟
void Boid::setElapsed(double e)
{
    this->elapsed = e;
}

// 运行三个函数，behavior、update和isOutBorders
void Boid::run()
{
    steeringBehavior();
    update();
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
    acceleration.mulScalar(this->elapsed);
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
    if (wanderDisSum > 4.0) {wanderDisSum *= -1;}
    if (wanderDisSum > 10.0) {wanderDisSum = 0.0;}
    wanderDisSum += this->elapsed;
    wanderDistance += wanderDisSum*this->elapsed;

    double randomClamped = ((rand())/(RAND_MAX+1.0)) - ((rand())/(RAND_MAX+1.0));
    // 1.对目标添加随机位移
    double JitterThisTimeSlice = wanderJitter * this->elapsed;
    wanderTarget.subVector(Vector2D(randomClamped * JitterThisTimeSlice, randomClamped * JitterThisTimeSlice));
    // 2.对目标标准化后，重新投影到圆边上
    wanderTarget.normalize();
    wanderTarget.mulScalar(wanderRadius);
    // 3.向前移动目标
    wanderTarget.addVector(Vector2D(wanderDistance, 0));
    // 4.把目标投影到世界空间
    wanderTarget.addVector(location);
    // 4.计算出智能体到达目标位置的力
    return seek(wanderTarget);
}

// 返回一个智能体到达目标的 力
Vector2D Boid::seek(Vector2D target)
{
    // 1. 计算预期速度，该速度从boid位置指向目标位置
    //  理想化速度，即为boid移动的最大速度
    Vector2D desired = target.subTwoVector(target, location);
    desired.normalize();
    desired.mulScalar(maxSpeed);
    desired.limit(maxForce);
    // 2. 移动所需的力 = 预期速度 - 当前速度
    return desired.subTwoVector(desired, velocity);
}