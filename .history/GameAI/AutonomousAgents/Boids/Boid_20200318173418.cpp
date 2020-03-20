#include <iostream>
#include <vector>
#include <string>
#include <math.h>
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

// 设置窗口大小
void Boid::setWindow(int width, int height)
{
    this->windowWidth = width;
    this->windowHeight = height;
}

// 运行三个函数，behavior、update和isOutBorders
void Boid::run()
{
    update();
    isOutBorders();
    std::cout << location.x << "    " << std::endl;
}

// 更新boid位置
void Boid::update()
{
    //To make the slow down not as abrupt
    acceleration.mulScalar(.4);
    // Update velocity
    velocity.addVector(acceleration);
    // Limit speed
    velocity.limit(maxSpeed);
    location.addVector(velocity);
    // Reset accelertion to 0 each cycle
    acceleration.mulScalar(0);
}

// 当boid飞出窗口，校正其位置
void Boid::isOutBorders()
{
    if (location.x < 0) location.x += this->windowWidth;
    if (location.y < 0) location.y += this->windowHeight;
    if (location.x > this->windowWidth) location.x -= this->windowWidth;
    if (location.y > this->windowHeight) location.y -= this->windowHeight;
}