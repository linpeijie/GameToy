#ifndef WORLD_H
#define WORLD_H
#include <iostream>
#include <vector>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "Boid.h"
#include "Vector2D.h"

class World
{
private:
    sf::RenderWindow window;
    int windowWidth;
    int windowHeight;

    // 用动态数组来保存图形和boids;
    float boidSize;
    std::vector<sf::CircleShape> shapes;
    std::vector<Boid> boids;
    void creBoids();
    void creBoid(int posX, int posY);

    inline void isOutWindow(int i);

    // 渲染和处理输入
    void render();
    void handleInput();

public:
    World()
    ~World() {}
    void run();
};

#endif
