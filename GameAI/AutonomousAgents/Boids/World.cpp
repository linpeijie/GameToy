#include "World.h"

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
    sf::Clock clock;
    elapsed = clock.restart();
    // 初始化类鸟群
    creBoids(elapsed.asSeconds());

    while(window.isOpen())
    {
        elapsed = clock.restart();
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
    }

    // 检测鼠标点击事件，绘制一个新的图形
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
    {
        // 获取鼠标位置
        sf::Vector2i mouseCoords = sf::Mouse::getPosition(window);
        creBoid(mouseCoords.x, mouseCoords.y, elapsed.asSeconds());
    }
}

// 渲染图形
void World::render()
{
    window.clear();
    // 计算 boid位置和航向，并同图形绑定
    for (int i = 0; i < shapes.size(); ++i)
    {
        window.draw(shapes[i]);
        //shapes[i].setPosition(boids[i].location.x, boids[i].location.y);
        shapes[i].setPosition(flock.getBoid(i).location.x, flock.getBoid(i).location.y);

        float theta = flock.getBoid(i).angle(flock.getBoid(i).velocity);
        shapes[i].setRotation(theta);

        // 当boid飞出窗口，校正位置
        isOutWindow(i);
    }

    // 计算每个boid的运动路径
    // for (auto& b: boids)
    // {
    //     b.setElapsed(elapsed.asSeconds());
    //     b.run();
    // }
    flock.flocking(elapsed.asSeconds());
    window.display();
}

// 创建一个类鸟群
void World::creBoids(double e)
{
    for (int i = 0; i < 50; ++i)
    {
        creBoid(windowWidth/2, windowHeight/2, e);
    }
}

// 在指定位置生成一个 个体
inline void World::creBoid(int posX, int posY, double e)
{
    Boid b((float)posX, (float)posY);
    b.setWindow(windowWidth, windowHeight);
    b.setElapsed(e);
    // 更改图形的视觉属性
    sf::CircleShape shape(8.f, 3);
    shape.setPosition(posX, posY);
    shape.setOutlineColor(sf::Color(0,255,0));
    shape.setFillColor(sf::Color::Green);
    shape.setOutlineColor(sf::Color::White);
    shape.setOutlineThickness(1);
    shape.setRadius(boidSize);
    // boid 和 shape 在数组中位置要一致
    //boids.push_back(b);
    flock.addBoid(b);
    shapes.push_back(shape);
}

inline void World::isOutWindow(int i)
{
    if (shapes[i].getPosition().x > windowWidth)
        shapes[i].setPosition(shapes[i].getPosition().x - windowWidth, shapes[i].getPosition().y);
    // If boid exits bottom boundary
    if (shapes[i].getPosition().y > windowHeight)
        shapes[i].setPosition(shapes[i].getPosition().x, shapes[i].getPosition().y - windowHeight);
        // If boid exits left boundary
    if (shapes[i].getPosition().x < 0)
        shapes[i].setPosition(shapes[i].getPosition().x + windowWidth, shapes[i].getPosition().y);
        // If boid exits top boundary
    if (shapes[i].getPosition().y < 0)
        shapes[i].setPosition(shapes[i].getPosition().x, shapes[i].getPosition().y + windowHeight);
}
