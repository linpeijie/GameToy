#ifndef GAME_H
#define GAME_H
#include <time.h>
#include "Player.h"
#include "Enemy.h"

class Game
{
private:
    int             playerHp;
    int             score;
    bool            hasBoss;
    bool            victory;
    bool            fail;
    sf::Time        elapsed;

    Player          *player;
    list<Enemy*>    allEnemy;

    sf::Texture     backgroundTexture;
    sf::Texture     gameoverTexture;
    sf::Sprite      background;
    sf::Font        font;
    sf::Text        mScore;
    sf::Text        mHP;
    sf::Music       BGM1;
    sf::Sound       fireSound;
    sf::SoundBuffer buffer;
    sf::RenderWindow window;

    void update();
    void handleInputs();
    void render();
    void enemyAction(float &timePassed);
    void checkCollide();

public:
    Game();
    ~Game()
    {
        delete player;
    }

    void run();
};

#endif
