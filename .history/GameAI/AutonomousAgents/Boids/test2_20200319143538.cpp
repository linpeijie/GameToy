#include "test2.h"

test2::test2()
{
    default_random_engine e(time(0));
    uniform_real_distribution<float> m(0, INT_MAX);

    float t = (m(e)/(INT_MAX)) * 360;
    //wanderTarget = Vector2D(wanderRadius * cos(t), wanderRadius * sin(t));
    cout<< " "<< t << " " << "  " << (m(e)/(INT_MAX)) * 360 << endl;
}