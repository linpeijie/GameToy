#include "Flock.h"

Boid Flock::getBoid(int i)
{
    return flock[i];
}

void Flock::addBoid(Boid b)
{
    flock.push_back(b);
}

void Flock::clearFlock()
{
    flock.clear();
}

void Flock::flocking(double elapsed)
{
    for (auto &b: flock)
    {
        b.setElapsed(elapsed);
        b.run(flock);
    }
}