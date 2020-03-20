#include <iostream>
#include <random>

class test2
{
private:
    // 圆半径
    float wanderRadius;
    // 圆离boid距离
    float wanderDistance;
    // 目标点随机抖动值
    float wanderJitter;
    //Vector2D wanderTarget;

public:
    test2() {}
    ~test2() {}
    test2(int i);
};