#ifndef BOID_H
#define BOID_H
#include <iostream>
#include <vector>
#include <stdlib.h>
#include "Vector2D.h"
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

    Vector2D location;
    Vector2D velocity;
    Vector2D acceleration;

    void run();
    void setWindow(int width, int height);
    void update();
    void isOutBorders();

};

#endif