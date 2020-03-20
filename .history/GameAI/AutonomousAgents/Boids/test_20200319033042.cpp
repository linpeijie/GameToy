#include <iostream>
#include <ctime>
#include <random>
#include "Vector2D.h"
#include "C2DMatrix.h"

int main()
{
    // 初始化wanderTarget位置
    wanderRadius = 30.f;
    wanderDistance = 10.f;
    wanderJitter = 5.f;
    float theta = (rand())/(RAND_MAX+1.0) * PI * 2;
    wanderTarget = Vector2D(wanderRadius * cos(theta), wanderRadius * sin(theta));

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
    // wanderTarget.x += location.x;
    // wanderTarget.y += location.y;

    //create a transformation matrix
	C2DMatrix matTransform;
	//and translate
	matTransform.Translate(location.x, location.y);
    //now transform the vertices
    matTransform.TransformVector2Ds(wanderTarget);
}