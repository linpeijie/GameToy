#include "Boid.h"
#include "Flock.h"

int Flock::getSize()
{
    return flock.size();
}

Boid Flock::getBoid(int i)
{
    return flock[i];
}

void Flock::addBoid(Boid b)
{
    flock.push_back(b);
}

void Flock::run()
{
    for (auto b: flock)
        b.run();
}

