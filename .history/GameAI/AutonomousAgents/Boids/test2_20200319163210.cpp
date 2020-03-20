#include <iostream>
#include <ctime>
#include <random>
#include "test2.h"

using namespace std;
#define	RAND_MAX 0x7fffffff
#define PI 3.14159265358

test2::test2(int i)
{

    //default_random_engine e(time(0));
    //uniform_real_distribution<float> m(0, INT_MAX);

    float t = (rand()/(RAND_MAX)) * PI * 2;

    cout << rand()/(RAND_MAX) << endl;
}