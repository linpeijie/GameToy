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

int main()
{
    default_random_engine e(time(0));
    uniform_real_distribution<float> m(0, INT_MAX);

    for (int i = 0; i < 100; ++i)
        cout << m(e) << endl;

    return 0;
}