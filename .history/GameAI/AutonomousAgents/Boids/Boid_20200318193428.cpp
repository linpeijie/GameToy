#include <iostream>
#include <vector>
#include <string>
#include <math.h>
#include "Boid.h"
#include "SFML/Graphics.hpp"

sf::VideoMode desktopTemp = sf::VideoMode::getDesktopMode();
const int window_height = desktopTemp.height;
const int window_width = desktopTemp.width;

#define w_height window_height
#define w_width window_width

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
}

// 更新boid位置
void Boid::update()
{
    location.x += 1;
    location.y += 1;
}

// 当boid飞出窗口，校正其位置
void Boid::isOutBorders()
{
    if (location.x < 0) location.x += w_width;
    if (location.y < 0) location.y += w_height;
    if (location.x > w_width) location.x -= w_width;
    if (location.y > w_height) location.y -= w_height;
}