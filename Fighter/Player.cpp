#include "includes/Player.h"

Player::Player():Entity()
{
    // 从png中切图
    this->setEntityTexture("resources/image/shoot.png", 0, 99, 102, 126);
    this->setTexture(*(getTexture()));
    sf::Transformable::setPosition(width/2 - 51, hight - 100);

    this->setSpeed(300);
    this->setHP(3);
}

// 战斗机开火
void Player::fire()
{
    playerBullets.push_back(new Bullet(this->getPosition().x+51, this->getPosition().y, hero));
    std::cout << "Fire!" << std::endl;
}

// 返回战斗机的子弹仓库
list<Bullet*> Player::getBullets()
{
    return playerBullets;
}

// 当子弹超出屏幕或击中敌人的时候，销毁子弹
void Player::destroyBullet(Bullet *&b)
{
    playerBullets.remove(b);
}