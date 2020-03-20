#ifndef BOID_H
#define BOID_H
#include <iostream>
#include <vector>
#include <stdlib.h>
#include "Vector2D.h"

// The Boid Class

class Boid
{
private:
    float maxSpeed;
    float maxForce;

public:
    Boid() {}
    Boid(float x, float y);

    Vector2D location;
    Vector2D velocity;
    Vector2D acceleration;

    void run(std::vector<Boid> boids);
    void update();
    void isOutBorders();

};

#endif