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

    // SFML绘制图形，创建一个类鸟群
    float boidSize;
    std::vector<sf::CircleShape> shapes;
    void genShapes(int size);
    void genShapes(sf::Vector2i mouseCoords);

    // 渲染和处理输入
    void render();
    void handleInput();

public:
    World();
    void run();
};

#endif
