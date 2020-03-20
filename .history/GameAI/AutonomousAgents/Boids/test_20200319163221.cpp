#include <iostream>
#include <ctime>
#include <random>
#include <math.h>
#include <stdlib.h>
#include <vector>
#include "test2.h"
#include <ctime>

using namespace std;
#define PI 3.14159265358

int main()
{
    default_random_engine e(time(0));

    for (int i = 0; i < 10; ++i)
        test2 testF(i);
    return 0;
}