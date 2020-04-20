#include "includes/Entity.h"

Entity::Entity():mTexture()
{
	HP = 1;
}

Entity::Entity(int _hp):mTexture()
{
	HP = _hp;
}

// 绘制Sprite的图案，设置位置、宽高
void Entity::setEntityTexture(const string filePath,int x,int y,int sizex,int sizey)
{
    mTexture.loadFromFile(filePath,sf::IntRect(x, y, sizex, sizey));
}

void Entity::setSpeed(int _speed)
{
    speed = _speed;
}

float Entity::getSpeed()
{
    return speed;
}

void Entity::setHP(int hp)
{
    HP = hp;
}

int Entity::getHP()
{
    return HP;
}

sf::Texture* Entity::getTexture()
{
    return &mTexture;
}

void Entity::hurted()
{
    HP--;
}

bool Entity::isAlive()
{
    return HP > 0;
}
