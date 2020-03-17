#include <iostream>
#include "World.h"
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

// 创建 World窗口
World::World()
{
    // 获取当前桌面的多媒体模式
    sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
    this->windowHeight = desktop.height;
    this->windowWidth = desktop.width;
    this->window.create(sf::VideoMode(windowHeight, windowWidth, desktop.bitsPerPixel), "Boids' World", sf::Style::None);

}

void World::run()
{
    while(window.isOpen())
    {
        handleInput();
        render();
    }
}

void World::handleInput()
{
    sf::Event event;
    while (window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
        {
            window.close();
        }
    }

}

void World::render()
{
    window.clear();
    window.display();
}