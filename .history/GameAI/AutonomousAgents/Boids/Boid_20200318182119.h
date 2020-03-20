#ifndef BOID_H
#define BOID_H
#include <iostream>
#include <vector>
#include <stdlib.h>
#include "Pvector.h"

// The Boid Class

class Boid
{
private:
    float maxSpeed;
    float maxForce;
    int windowWidth;
    int windowHeight;

public:
    Boid() {}
    Boid(float x, float y);

    Pvector location;
    Pvector velocity;
    Pvector acceleration;

    void run();
    void setWindow(int width, int height);
    void update();
    void isOutBorders();

};

#endif