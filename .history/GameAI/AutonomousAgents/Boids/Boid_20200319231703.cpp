#include "Boid.h"

using namespace std;

#define PI 3.14159265358
#define	RAND_MAX 0x7fffffff

Boid::Boid(float x, float y):
    acceleration(Vector2D(0,0)),
    velocity(Vector2D(rand()%3 - 2, rand()%3 - 2)),
    location(Vector2D(x, y)),
    maxSpeed(3.5),
    maxForce(0.5),
    wanderRadius(6.0f),
    wanderDistance(2.0f),
    wanderJitter(60.f)
{
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

// 行为模式
void Boid::steeringBehavior()
{
    // 计算每种行为模式下的受力情况
    Vector2D wan = wander();
    // 按情况考虑是否缩放物体当前受力
    wan.mulScalar(1.0);
    // 计算综合受力
    applyForce(wan);
}

// 更新boid位置
void Boid::update()
{
    // 计算瞬时速度  v = v0 + at
    acceleration.mulScalar(this->elapsed);
    velocity.addVector(acceleration);
    // 当速度超过maxSpeed的时候，使其做匀速运动
    velocity.limit(maxSpeed);
    // 移动物体
    location.addVector(velocity);
    // 当前时刻受力清零，准备接受下一时刻的 受力
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

// 计算下一时刻物体的 受力
void Boid::applyForce(Vector2D force)
{
    acceleration.addVector(force);
}

// 控制boid随机徘徊
Vector2D Boid::wander()
{
    wanderTime += this->elapsed;

    double randomClamped = ((rand())/(RAND_MAX+1.0)) - ((rand())/(RAND_MAX+1.0));
    // 1.对目标添加随机位移
    double JitterThisTimeSlice = wanderJitter * this->elapsed;
    wanderTarget.addVector(Vector2D(randomClamped * JitterThisTimeSlice, randomClamped * JitterThisTimeSlice));
    // 2.对目标标准化后，重新投影到圆边上
    wanderTarget.normalize();
    wanderTarget.mulScalar(wanderRadius);
    // 3.向前移动目标
    wanderTarget.addVector(Vector2D(wanderDistance, 0));
    // 4.把目标投影到世界空间
    // 也可以直接把target加上boid当前坐标  wanderTarget.addVector(location);
	C2DMatrix matTransform;
	matTransform.Translate(location.x, location.y);
    matTransform.TransformVector2Ds(wanderTarget);
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