#include <iostream>
#include <vector>
#include <string>
#include <math.h>
#include "SFML/Graphics.hpp"
#include "Boid.h"

#define PI 3.14159265358

Boid::Boid(float x, float y)
{
    acceleration = Vector2D(0, 0);
    velocity = Vector2D(rand()%3 - 2, rand()%3 - 2);
    location = Vector2D(x, y);
    this->maxSpeed = 3.5;
    this->maxForce = 0.5;
}

void Boid::run(std::vector <Boid> v)
{

}