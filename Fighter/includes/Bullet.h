#ifndef BULLET_H
#define BULLET_H
#include "Entity.h"

class Bullet: public Entity
{
private:

public:
    Bullet();
    Bullet(int _x, int _y, int type)
    {
        if(type != hero)this->setEntityTexture("resources/image/shoot.png",69,78,9,21);
        else this->setEntityTexture("resources/image/shoot.png",1004,987,9,21);

	    this->setTexture(*(getTexture()));
	    sf::Transformable::setPosition(_x,_y);

        this->setSpeed(500);
    };
};

#endif