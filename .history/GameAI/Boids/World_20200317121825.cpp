#include <iostream>
#include "World.h"
#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"

// 创建 World窗口
World::World()
{
    this->boidSize = 3.0;
    // 获取当前桌面的多媒体模式
    sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
    this->windowWidth = desktop.width;
    this->windowHeight = desktop.height;
    this->window.create(sf::VideoMode(windowWidth, windowHeight, desktop.bitsPerPixel), "Boids", sf::Style::None);
}

// 让世界转动吧！
void World::run()
{
    // 绘制图形
    for (int i = 0; i < 10; ++i)
    {
        sf::CircleShape shape(8.f, 3);
        shape.setPosition(windowWidth, windowHeight); // Testing purposes, starts all shapes in the center of screen.
        shape.setOutlineColor(sf::Color(0,255,0));
        shape.setFillColor(sf::Color::Green);
        shape.setOutlineColor(sf::Color::White);
        shape.setOutlineThickness(1);
        shape.setRadius(boidSize);

        shapes.push_back(shape);
    }


    while(window.isOpen())
    {
        handleInput();
        render();
    }
}

// 处理各种键盘输入事件
void World::handleInput()
{
    sf::Event event;
    while (window.pollEvent(event))
    {
        if ((event.type == sf::Event::Closed) ||
            (event.type == sf::Event::KeyPressed &&
             event.key.code == sf::Keyboard::Escape) ||
            (event.type == sf::Event::KeyPressed &&
             event.key.code == sf::Keyboard::BackSpace) ||
            (event.type == sf::Event::KeyPressed &&
             event.key.code == sf::Keyboard::X))
        {
            window.close();
        }
    }

}

// 渲染图形
void World::render()
{
    window.clear();

    window.draw(shapes[0]);

    window.display();
}