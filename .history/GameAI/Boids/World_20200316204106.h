
#include <iostream>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#ifndef WORLD_H
#define WORLD_H

class World
{
private:
    sf::RenderWindow window;
    int windowWidth;
    int windowHeight;

    // 渲染和处理输入
    void render();
    void handleInput();

public:
    World();
    void run();
};


#endif
