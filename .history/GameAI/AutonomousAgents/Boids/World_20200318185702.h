#ifndef WORLD_H
#define WORLD_H
#include <iostream>
#include <vector>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "Flock.h"
#include "Boid.h"
#include "Vector2D.h"

class World
{
private:
    sf::RenderWindow window;
    int windowWidth;
    int windowHeight;

    // SFML绘制图形，创建一个类鸟群;
    float boidSize;
    //Flock flock;
    std::vector<sf::CircleShape> shapes;
    std::vector<Boid> boids;
    void creBoids();
    void creBoid(int posX, int posY);

    void isOutWindow(int i);

    // 渲染和处理输入
    void render();
    void handleInput();

public:
    World();
    void run();
};

#endif
