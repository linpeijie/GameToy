#ifndef WORLD_H
#define WORLD_H
#include <iostream>
#include <vector>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

class World
{
private:
    sf::RenderWindow window;
    int windowWidth;
    int windowHeight;

    float boidSize;
    std::vector<sf::CircleShape> shapes;
    void drawShapes(int size);

    // 渲染和处理输入
    void render();
    void handleInput();

public:
    World();
    void run();
};

#endif
