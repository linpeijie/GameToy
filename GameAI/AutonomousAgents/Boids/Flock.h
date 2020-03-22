#ifndef FLOCK_H
#define FLOCK_H
#include <iostream>
#include <vector>
#include "Boid.h"

using namespace std;

// -----------------Flock-----------------
// flock: 存储环境内的全部boid
// ---------------------------------------

class Flock
{
public:
    Flock() {}
    ~Flock() {}

    vector<Boid> flock;
    Boid getBoid(int i);
    void addBoid(Boid b);
    void clearFlock();
    void flocking(double elapsed);
};

#endif