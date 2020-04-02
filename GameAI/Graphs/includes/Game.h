#ifndef GAME_H
#define GAME_H
#include <iostream>
#include <vector>
#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"
#include "SFML/System.hpp"
#include "../includes/Tile.h"
#include "../Astar/Astar.h"

using namespace std;

struct Node
{
    Tile t;
    shared_ptr<Node> next;
    Node(Tile _t):t(_t),next(NULL) {}
};

class Game
{
private:
    sf::RenderWindow window;

    const unsigned int width;
    const unsigned int  height;
    int tileSize;
    int horizontalTiles;

    vector<Tile> tiles;
    shared_ptr<Node> drawPaths;
    vector<vector<int> > maze;
    Tile sourceTile;
    Tile targetTile;

    bool running;
    sf::Keyboard::Key keyCode;

    // 路径规划算法
    Point source;
    Point target;
    Astar astar;

public:
    Game();
    ~Game() {}

    void run();
    // 启动寻路算法
    void runPathPlaning();

    void drawScene();
    void clear();
    void setSourceOrTarget(sf::Keyboard::Key key);
    int indexAt(sf::Vector2f position);

    // 处理输入和渲染
    void handleInput();
    void render();
};

#endif