#include <iostream>
#include <ctime>
#include <random>
#include "test2.h"

using namespace std;

test2::test2(int i)
{
    // 初始化wanderTarget位置
    wanderRadius = 6.f;
    wanderDistance = 1.f;
    wanderJitter = 2.f;

    default_random_engine e(time(0));
    uniform_real_distribution<float> m(0, INT_MAX);

    float t = (m(e)/(INT_MAX)) * 360;
    cout << t << endl;
}