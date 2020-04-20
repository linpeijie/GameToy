#ifndef ENEMY_H
#define ENEMY_H
#include "Bullet.h"

class Enemy:public Entity
{
private:
    int                  type;
    list<Bullet*>        enemyBullets;
    sf::Texture          crashTexture1;
    sf::Texture          crashTexture2;
    sf::Texture          crashTexture3;
    sf::Sound            crashSound1,crashSound2;
    sf::SoundBuffer      buffer1, buffer2;

public:
    Enemy();
    Enemy(int _type);
    ~Enemy()
    {
        for (auto &b: enemyBullets)
            delete b;
    }

    list<Bullet*>   getBullets();
    void            destroyBullet(Bullet *&b);
    void            setPosition();
    void            fire();
    void            crash();
    int             getType() {return type;};

};

#endif