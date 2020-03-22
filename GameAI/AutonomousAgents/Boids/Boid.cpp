#include "Boid.h"

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
    //初始化目标位置
    for(auto &e: neighbor)
        e = 0;
    float theta = (rand())/(RAND_MAX+1.0) * PI * 2;
    wanderTarget = Vector2D(wanderRadius * cos(theta), wanderRadius * sin(theta));
}

// 设置窗口大小
void Boid::setWindow(int width, int height)
{
    winWidth = width;
    winHeight = height;
}

// 增量时间
void Boid::setElapsed(double e)
{
    this->elapsed = e;
}

// 让物体动起来
void Boid::run(vector<Boid> boids)
{
    steeringBehavior(boids);
    update();
    isOutBorders();
}

// 更新物体位置
void Boid::update()
{
    // 计算瞬时速度  v = v0 + at
    acceleration.mulScalar(this->elapsed);
    velocity.addVector(acceleration);
    // 当速度超过maxSpeed的时候，减小其速度
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

// 行为模式
void Boid::steeringBehavior(vector<Boid> boids)
{
    // 计算每种行为模式下的受力情况
    Vector2D coh = cohesion(boids);
    Vector2D sep = separation(boids);
    Vector2D ali = alignment(boids);
    Vector2D wan = wander();
    // 按情况考虑是否缩放物体当前受力
    sep.mulScalar(1.5f);
    ali.mulScalar(1.0f);
    coh.mulScalar(1.0f);
    wan.mulScalar(0.1f);
    // 计算综合受力
    applyForce(sep);
    applyForce(ali);
    applyForce(coh);
    applyForce(wan);
}

// 体积排斥or分离
// 让智能体之间保持一定距离
Vector2D Boid::separation(vector<Boid> boids)
{
    float sepDistance = 20;
    Vector2D steeringForce(0, 0);
    int count = 0;

    // 计算出智能体邻域内的全部受力情况
    // 力的大小反比与智能体到它临近智能体的距离，也就是往反方向运动
    for (int i = 0; i < boids.size(); ++i)
    {
        if (neighbor[i] == 1)
        {
            float d = location.distance(boids[i].location);
            if ((d > 0) && (d < sepDistance))
            {
                Vector2D diff(0, 0);
                diff = diff.subTwoVector(location, boids[i].location);
                diff.normalize();
                diff.divScalar(d);
                steeringForce.addVector(diff);
                count++;
            }
        }
    }

    // 计算平均受力
    if (count > 0) steeringForce.divScalar((float)count);
    if (steeringForce.magnitude() > 0)
    {
        steeringForce.normalize();
        steeringForce.mulScalar(maxSpeed);
        steeringForce.subVector(velocity);
        steeringForce.limit(maxForce);
    }

    return steeringForce;
}

// 队列or速度对齐
// 计算邻域内智能体的平均速度，使智能体与其一直
Vector2D Boid::alignment(vector<Boid> boids)
{
    float nDistance = 50;
    Vector2D sum(0, 0);
    int count = 0;

    // 计算邻域内全部合力
    for (int i = 0; i < boids.size(); ++i)
    {
        if (neighbor[i] == 1)
        {
            float d = location.distance(boids[i].location);
            if ((d > 0) && (d < nDistance)) {
                sum.addVector(boids[i].velocity);
                count++;
            }
        }
    }

    // 计算智能体受力
    if (count > 0) {
        sum.divScalar((float)count);
        sum.normalize();
        sum.mulScalar(maxSpeed);

        Vector2D steeringForce;
        steeringForce = steeringForce.subTwoVector(sum, velocity);
        steeringForce.limit(maxForce);
        return steeringForce;
    } else return Vector2D(0, 0);
}

// 聚集倾向
// 每个智能体找到邻域内群体的重心,计算出运动到重心的受力
// 重心计算公式： x=(x1+x2+……+xn)/n  y=(y1+y2+……+yn)/n
Vector2D Boid::cohesion(vector<Boid> boids)
{
    float nDistance = 50;
    int count = 0;
    Vector2D center(0, 0);

    for (int i = 0; i < boids.size(); ++i)
    {
        float d = location.distance(boids[i].location);
        if (d > 0 && d < nDistance)
        {
            neighbor[i] = 1;
            center.addVector(boids[i].location);
            count++;
        }else neighbor[i] = 0;
    }

    if (count > 0)
    {
        center.divScalar((float)count);
        return seek(center);
    }else return Vector2D(0, 0);

}

// 控制物体徘徊
Vector2D Boid::wander()
{
    // 生成-1到1之间的随机数
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

// 输入目标位置向量，返回智能体 受力
Vector2D Boid::seek(Vector2D target)
{
    // 1. 计算预期速度，该速度从智能体位置指向目标位置
    //  理想化速度，即为智能体移动的最大速度
    Vector2D desired = target.subTwoVector(target, location);
    desired.normalize();
    desired.mulScalar(maxSpeed);
    desired.limit(maxForce);
    // 2. 智能体受力= 预期速度 - 当前速度
    return desired.subTwoVector(desired, velocity);
}

// 计算出速度的角度，使图形的方向跟速度方向保持一致
float Boid::angle(Vector2D v)
{
    // From the definition of the dot product
    float angle = (float)(atan2(v.x, -v.y) * 180 / PI);
    return angle;
}

