#ifndef WORLD_H
#define WORLD_H
#include <iostream>
#include <vector>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include "Boid.h"
#include "Flock.h"
#include "Vector2D.h"

using namespace std;

class World
{
private:
    sf::RenderWindow window;
    sf::Time elapsed;
    int windowWidth;
    int windowHeight;

    // 用动态数组来保存图形和boids;
    float boidSize;
    vector<sf::CircleShape> shapes;
    //vector<Boid> boids;
    Flock flock;

    void creBoids(double e);
    void creBoid(int posX, int posY, double e);

    void isOutWindow(int i);

    // 渲染和处理输入
    void render();
    void handleInput();

public:
    World();
    void run();
};

#endif
