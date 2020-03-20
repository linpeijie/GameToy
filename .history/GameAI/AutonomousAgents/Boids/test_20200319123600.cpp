#include <iostream>
#include <ctime>
#include <random>
#include <math.h>
#include <stdlib.h>
#include <vector>

using namespace std;
#define PI 3.14159265358

int main()
{
    default_random_engine e(time(0));
    uniform_real_distribution<float> m(0, INT_MAX);

    for (int i = 0; i < 100; ++i)
        cout << (m(e))/(INT_MAX) * PI * 2 << endl;

    return 0;
}