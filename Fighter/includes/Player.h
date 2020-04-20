#ifndef PLAYER_H
#define PLAYER_H
#include "Bullet.h"

class Player: public Entity
{
private:
    list<Bullet*> playerBullets;

public:
    Player();
    ~Player()
    {
        for (auto &b: playerBullets)
            delete b;
        std::cout << "游戏退出，销毁战斗机！" << std::endl;
    }

    list<Bullet*>   getBullets();
    void            destroyBullet(Bullet *&b);
    void            setPosition();
    void            fire();
    void            crash();
};

#endif