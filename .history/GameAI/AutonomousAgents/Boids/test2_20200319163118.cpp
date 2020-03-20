#include <iostream>
#include <ctime>
#include <random>
#include "test2.h"

using namespace std;
#define	RAND_MAX 0x7fffffff

test2::test2(default_random_engine e)
{

    //default_random_engine e(time(0));
    //uniform_real_distribution<float> m(0, INT_MAX);

    float t = (rand()/(RAND_MAX)) * 360;

    cout << t << endl;
}