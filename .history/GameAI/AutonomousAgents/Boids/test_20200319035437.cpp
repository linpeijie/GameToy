#include <iostream>
#include <ctime>
#include <random>
#include <math.h>
#include <stdlib.h>
#include <vector>
#include "Vector2D.h"
#include "C2DMatrix.h"

using namespace std;
#define PI 3.14159265358
#define	RAND_MAX 0x7fffffff

int main()
{
    default_random_engine e(time(0));
    uniform_real_distribution<float> u(0, RAND_MAX);

    // 初始化wanderTarget位置
    float wanderRadius = 6.f;
    float wanderDistance = 1.f;
    float wanderJitter = 10.f;
    float theta = (rand()/(RAND_MAX+1.0)) * PI * 2;
    cout << theta << endl;
    Vector2D wanderTarget = Vector2D(wanderRadius * cos(theta), wanderRadius * sin(theta));
    cout << wanderTarget.x << "  " << wanderTarget.y << endl;

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
    float x = wanderTarget.x + 1.0;
    float y = wanderTarget.y + 1.0;
    cout << x << "  " << y << endl;

    //create a transformation matrix
	C2DMatrix matTransform;
	//and translate
	matTransform.Translate(1.0, 1.0);
    //now transform the vertices
    matTransform.TransformVector2Ds(wanderTarget);
    cout << wanderTarget.x << "  " << wanderTarget.y << endl;

    return 0;
}