#include <iostream>
#include "World.h"
#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"

// 创建 World窗口
World::World()
{
    this->boidSize = 10.0;
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
    drawShapes(10);

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
        // 退出窗口
        if ((event.type == sf::Event::Closed) ||
            (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape))
        {
            window.close();
        }

        // 点击鼠标左键，绘制一个新的图形
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            sf::Vector2i mouseCoords = sf::Mouse::getPosition(window);
            drawShapes(mouseCoords);
        }
    }

}

// 渲染图形
void World::render()
{
    window.clear();

    for (int i = 0; i < shapes.size(); ++i)
    {
        window.draw(shapes[i]);

        //shapes[i].setPosition(windowWidth/2, windowHeight/2);
    }

    window.display();
}

// 绘制图形，初始化
void World::drawShapes(int size)
{
    for (int i = 0; i < size; ++i)
    {
        sf::CircleShape shape(8.f, 3);

        // 更改图形的视觉属性
        shape.setPosition(windowWidth, windowHeight); // Testing purposes, starts all shapes in the center of screen.
        shape.setOutlineColor(sf::Color(0,255,0));
        shape.setFillColor(sf::Color::Green);
        shape.setOutlineColor(sf::Color::White);
        shape.setOutlineThickness(1);
        shape.setRadius(boidSize);

        shapes.push_back(shape);
    }
}

// 绘制图形，鼠标事件
void World::drawShapes(sf::Vector2i mouseCoords)
{
    sf::CircleShape shape(8.f, 3);

    // 更改图形的视觉属性
    shape.setPosition(mouseCoords.x, mouseCoords.y); // Testing purposes, starts all shapes in the center of screen.
    shape.setOutlineColor(sf::Color(0,255,0));
    shape.setFillColor(sf::Color::Green);
    shape.setOutlineColor(sf::Color::White);
    shape.setOutlineThickness(1);
    shape.setRadius(boidSize);

    shapes.push_back(shape);
}