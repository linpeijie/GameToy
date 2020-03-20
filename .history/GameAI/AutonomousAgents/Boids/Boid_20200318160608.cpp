#include <iostream>
#include <vector>
#include <string>
#include <math.h>
#include "SFML/Graphics.hpp"
#include "Boid.h"

sf::VideoMode desktopTemp = sf::VideoMode::getDesktopMode();
const int window_height = desktopTemp.height;
const int window_width = desktopTemp.width;

#define PI 3.14159265358

Boid::Boid(int width, int height)
{
    acceleration = Vector2D(0, 0);
    velocity = Vector2D(rand()%3 - 2, rand()%3 - 2);
    location = Vector2D(width/2, height/2);
    this->maxSpeed = 3.5;
    this->maxForce = 0.5;
    this->windowWidth = width;
    this->windowHeight = height;
}

void Boid::run(std::vector<Boid> boids)
{
    update();
    isOutBorders();
}

void Boid::update()
{
    // 按一定的速度飞行
    acceleration.mulScalar(.4);
    velocity.addVector(acceleration);
    // 限制飞行速度
    velocity.limit(maxSpeed);
    location.addVector(velocity);

    acceleration.mulScalar(0);
}

void Boid::isOutBorders()
{
    if (location.x < 0) location.x += this->windowWidth;
    if (location.y < 0) location.y += this->windowHeight;
    if (location.x > this->windowWidth) location.x -= this->windowWidth;
    if (location.y > this->windowHeight) location.y -= this->windowHeight;

}