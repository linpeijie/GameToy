#ifndef FLOCK_H
#define FLOCK_H

#include <iostream>
#include <vector>
#include "Boid.h"

class FLock
{
public:
    FLock() {}
    // 存储每个 boid
    vector<Boid> flock;
    // 绑定boid到图形上
    void addBoid(Boid b);

    Boid getBoid(int i);
    int getSize();

    void run();
};

#endif