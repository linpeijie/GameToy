#include "includes/Game.h"

Game::Game():
    playerHp(3),
    score(0),
    fail(false),
    elapsed(sf::seconds(0.01f)),
    victory(false),
    hasBoss(false),
    player(new Player)
{
    window.create(sf::VideoMode{width, hight}, "Path Planning");
    window.setFramerateLimit(60);
    // 加载图片
    backgroundTexture.loadFromFile("resources/image/background.png");
    gameoverTexture.loadFromFile("resources/image/gameover.png");
    background.setTexture(backgroundTexture);
    // srand((unsigned) time(NULL));

    // 加载字体
    font.loadFromFile("resources/font/STHeiti Light.ttc");
    mScore.setFont(font);
    mHP.setFont(font);
    mScore.setPosition(0,0);
    mHP.setPosition(0,25);

    // 加载音效
    BGM1.openFromFile("resources/sound/game_music.ogg");
    BGM1.setLoop(true);
    BGM1.play();
    BGM1.setVolume(25.0f);
    // 不能用sf::Music来存放需要多次播放的音效，不然只能播放一次
    buffer.loadFromFile("resources/sound/bullet.ogg");
    fireSound.setBuffer(buffer);
}

void Game::run()
{
    sf::Clock clock;
    elapsed = clock.restart();
    float timePassed = 0.0f;

    while(window.isOpen())
    {
        handleInputs();
        enemyAction(timePassed);
        update();
        checkCollide();
        render();
        timePassed += elapsed.asSeconds();
        elapsed = clock.restart();
    }
}

void Game::handleInputs()
{
    sf::Event event;

    while (window.pollEvent(event))
    {
        // 退出窗口
        if ((event.type == sf::Event::Closed) ||
            event.key.code == sf::Keyboard::Escape)
        {
            window.close();
        }
        // 战斗机开火
        if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space)
        {
            fireSound.play();
            player->fire();
        }
    }

    // 控制战斗机移动
    sf::Vector2f movement(0.0f, 0.0f);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && player->getPosition().y > 0)
        movement.y -= player->getSpeed();
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && player->getPosition().y < 700)
        movement.y += player->getSpeed();
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && player->getPosition().x > 0)
        movement.x -= player->getSpeed();
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && player->getPosition().x < 380)
        movement.x += player->getSpeed();
    player->move(movement*elapsed.asSeconds());
}

void Game::update()
{

    // 子弹逻辑
    for (auto &b: player->getBullets())
    {
        sf::Vector2f movement(0.0f, 0.0f);
        movement.y -= b->getSpeed();
        b->move(movement * elapsed.asSeconds());
        // 当子弹飞出屏幕的时候销毁子弹
        if (b->getPosition().y < 0)
            player->destroyBullet(b);

    }

    for (auto &e: allEnemy)
    {
        for (auto &b: e->getBullets())
        {
            sf::Vector2f movement(0.0f, 0.0f);
            movement.y += b->getSpeed();
            b->move(movement * elapsed.asSeconds());
            // 当子弹飞出屏幕的时候销毁子弹
            if (b->getPosition().y > 800)
                e->destroyBullet(b);
        }
    }

    // 销毁敌机
    for (auto it = allEnemy.begin(); it != allEnemy.end();)
    {
        if ((*it)->getHP() <= 0)
        {
            (*it)->crash();
            allEnemy.erase(it++);
            score++;
        }
        else
            ++it;
    }
}

void Game::render()
{
    window.clear();
    window.draw(background);

    window.draw(*player);
    for (auto &e: allEnemy)
        window.draw(*e);

    // 渲染子弹
    for (auto &b: player->getBullets())
        window.draw(*b);

    for (auto &e: allEnemy)
        for (auto &b: e->getBullets())
            window.draw(*b);

    //显示字符串
    char s[20],s2[20]="Score: ";
    snprintf(s,9,"%d",score);
    strcat(s2,s);
    mScore.setString(s2);
    window.draw(mScore);

    strcpy(s2,"HP: ");
    snprintf(s,9,"%d",player->getHP());
    strcat(s2,s);
    mHP.setString(s2);
    window.draw(mHP);

    window.display();
}

// 敌机行动逻辑
void Game::enemyAction(float &timePassed)
{
    // if(this->score > 50 && !hasBoss)
    // {
    //     allEnemy.push_back(new Enemy(boss));
    // }

    if(timePassed > 2.0f)
    {
        timePassed = 0.0f;

        allEnemy.push_back(new Enemy(normal));
        allEnemy.back()->fire();

        if (rand()%100 > 80 || (score!=0 && score%4==0))
        {
            allEnemy.push_back(new Enemy(elite));
            allEnemy.back()->fire();
        }
    }

    // 敌机移动
    for (auto &e: allEnemy)
    {
        sf::Vector2f movement(0.0f, 0.0f);
        movement.y += e->getSpeed();
        e->move(movement*elapsed.asSeconds());
    }
}

// 检测子弹碰撞，机体碰撞
void Game::checkCollide()
{
    //检测战斗机子弹碰撞
    for (auto &pb: player->getBullets())
    {
        for (auto &enemy: allEnemy)
        {
            if (pb->getGlobalBounds().intersects(enemy->getGlobalBounds()))
            {
                enemy->hurted();
                player->destroyBullet(pb);
            }
        }
    }

    //检测敌机子弹、机体碰撞
    for (auto &enemy: allEnemy)
    {
        for (auto &b: enemy->getBullets())
            if (b->getGlobalBounds().intersects(player->getGlobalBounds()))
            {
                enemy->destroyBullet(b);
                player->hurted();
            }

        if (enemy->getGlobalBounds().intersects(player->getGlobalBounds()))
        {
            enemy->hurted();
            player->hurted();
        }
    }

}
