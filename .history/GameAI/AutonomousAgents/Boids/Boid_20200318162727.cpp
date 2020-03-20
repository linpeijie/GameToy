#include <iostream>
#include <vector>
#include <string>
#include <math.h>
#include "Boid.h"

#define PI 3.14159265358

Boid::Boid(int x, int y)
{
    acceleration = Vector2D(0, 0);
    velocity = Vector2D(rand()%3 - 2, rand()%3 - 2);
    location = Vector2D(x, y);
    this->maxSpeed = 3.5;
    this->maxForce = 0.5;
}

void Boid::setWindow(int width, int height)
{
    this->windowWidth = width;
    this->windowHeight = height;
}

void Boid::run()
{
    update();
    isOutBorders();
}

void Boid::update()
{
    location.x += 1;
    location.y += 1;
}

void Boid::isOutBorders()
{
    if (location.x < 0) location.x += this->windowWidth;
    if (location.y < 0) location.y += this->windowHeight;
    if (location.x > this->windowWidth) location.x -= this->windowWidth;
    if (location.y > this->windowHeight) location.y -= this->windowHeight;

}