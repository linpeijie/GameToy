#include "includes/Game.h"

Game::Game():
    width(1280),
    height(720),
    tileSize(40),
    horizontalTiles(1280/40),
    running(false),
    source(0,0),
    target(17,31),
    keyCode(sf::Keyboard::A)
{
    window.create(sf::VideoMode{width, height}, "Path Planning");
    window.setFramerateLimit(60);
    // 初始化 方格地图
    for (int y = 0; y <= height; y += tileSize)
    {
        for (int x = 0; x < width; x += tileSize)
        {
            Tile t(sf::IntRect(x, y, tileSize, tileSize));
            tiles.push_back(t);
        }
    }

    maze = vector<vector<int>>(height/tileSize, vector<int>(width/tileSize, 0));

    sourceTile = Tile(sf::IntRect(0, 0, tileSize, tileSize), tile::Start);
    targetTile = Tile(sf::IntRect(width - tileSize, height - tileSize, tileSize, tileSize), tile::End);
    // 寻路算法初始化
    astar = Astar(maze);
    drawPaths = shared_ptr<Node>(new Node(sourceTile));
}

void Game::run()
{
    sf::Clock clock;

    while (window.isOpen())
    {
        handleInput();
        render();

        if (running && drawPaths)
        {
            // Slow down A*
            sf::Time time = clock.getElapsedTime();
            bool timePassed = time.asMilliseconds() > 100.f;

            if (timePassed)
            {
                sf::Vector2i position = drawPaths->t.getIndex();
                tiles[position.y*horizontalTiles + position.x].setID(drawPaths->t.getID());
                drawPaths = drawPaths->next;
                clock.restart();
            }
        }
    }
}

// 处理键盘输入
inline void Game::handleInput()
{
    sf::Event event;

    while (window.pollEvent(event))
    {
        switch (event.type)
        {
        case sf::Event::Closed:
            window.close();
            break;
        case sf::Event::KeyPressed:
            if (event.key.code == sf::Keyboard::Escape)
            {
                window.close();
            }
            else if (event.key.code == sf::Keyboard::A)
            {
                keyCode = sf::Keyboard::A;
            }
            else if (event.key.code == sf::Keyboard::R)
            {
                // 只有重置地图后才能再次运行
                if (!running)
                {
                    running = true;
                    // 将 tiles 映射到 maze
                    for (auto &tile: tiles)
                    {
                        if (tile.getID() == tile::Wall)
                        {
                            sf::Vector2i p = tile.getIndex();
                            maze[p.y][p.x] = 1;
                        }
                    }
                    astar.setMaze(maze);

                    runPathPlaning();
                }
            }
            else if (event.key.code == sf::Keyboard::C)
            {
                clear();
            }
            else if (event.key.code == sf::Keyboard::S)
            {
                if (!running)
                    setSourceOrTarget(sf::Keyboard::S);
            }
            else if(event.key.code == sf::Keyboard::T)
            {
                if (!running)
                    setSourceOrTarget(sf::Keyboard::T);
            }
            break;
        default:
            break;
        }
    }

    // 绘制墙壁节点
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))
    {
        sf::Vector2i mousePos = sf::Mouse::getPosition(window);
        sf::Vector2f mousePosition(mousePos.x, mousePos.y);
        tiles[indexAt(mousePosition)].setID(tile::Wall);
    }
}

inline void Game::render()
{
    window.clear();
    drawScene();
    window.display();
}

// 启动路径规划算法，返回查找路径
void Game::runPathPlaning()
{
    shared_ptr<Node> head = drawPaths;

    if (running && keyCode == sf::Keyboard::A)
    {
        // A*算法 计算路径
        list<shared_ptr<Point> > path = astar.GetPath(source, target, false);
        list<shared_ptr<Point> > path2 = astar.getSearchPath();

        for (auto &tile: path2)
        {
            Tile t(sf::IntRect(tile->y*tileSize, tile->x*tileSize, tileSize, tileSize), tile::SearchPath);
            shared_ptr<Node> p(new Node(t));
            drawPaths->next = p;
            drawPaths = drawPaths->next;
        }

        for (auto &tile: path)
        {
            Tile t(sf::IntRect(tile->y*tileSize, tile->x*tileSize, tileSize, tileSize), tile::Path);
            shared_ptr<Node> p(new Node(t));
            drawPaths->next = p;
            drawPaths = drawPaths->next;
        }
    }

    drawPaths = head->next;
}

// 绘制计算后的所有方格
inline void Game::drawScene()
{
    for (const auto& tile: tiles)
        window.draw(tile);

    window.draw(sourceTile);
    window.draw(targetTile);
}

// 重置地图
void Game::clear()
{
    for (auto &tile: tiles)
        tile.setID(tile::Empty);

    maze = vector<vector<int>>(height/tileSize, vector<int>(width/tileSize, 0));
    astar.setMaze(maze);

    sourceTile = Tile(sf::IntRect(0, 0, tileSize, tileSize), tile::Start);
    targetTile = Tile(sf::IntRect(width - tileSize, height - tileSize, tileSize, tileSize), tile::End);
    drawPaths = shared_ptr<Node>(new Node(sourceTile));
    running = false;
}

// 设置起始节点、目标节点
void Game::setSourceOrTarget(sf::Keyboard::Key key)
{
    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
    const int x = static_cast<int>(mousePos.x - (mousePos.x % tileSize));
    const int y = static_cast<int>(mousePos.y- (mousePos.y % tileSize));

    if (key == sf::Keyboard::S)
    {
        sourceTile = Tile(sf::IntRect(x, y, tileSize, tileSize), tile::Start);
        sf::Vector2i s = sourceTile.getIndex();
        source = Point(s.y, s.x);
    }
    else
    {
        targetTile = Tile(sf::IntRect(x, y, tileSize, tileSize), tile::End);
        sf::Vector2i t = targetTile.getIndex();
        target = Point(t.y, t.x);
    }
}

// 根据鼠标的坐标，计算方格在数组中的位置
inline int Game::indexAt(sf::Vector2f position)
{
    auto positionX = static_cast<int>(position.x);
	auto positionY = static_cast<int>(position.y);

	positionX = (positionX - (positionX % tileSize)) / tileSize;
	positionY = (positionY - (positionY % tileSize)) / tileSize;

	return (positionY*(horizontalTiles) + positionX);
}
