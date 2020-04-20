#include "includes/Enemy.h"

Enemy::Enemy(int _type):Entity()
{
    if (_type == elite)
    {
        this->setEntityTexture("resources/image/shoot.png",0,0,69,95);
        this->setTexture(*(getTexture()));
        crashTexture1.loadFromFile("resources/image/shoot.png",sf::IntRect(534, 653, 69, 95));
        crashTexture2.loadFromFile("resources/image/shoot.png",sf::IntRect(672, 653, 69, 95));
        crashTexture3.loadFromFile("resources/image/shoot.png",sf::IntRect(741, 653, 69, 95));
        this->setHP(2);
        this->setSpeed(100);
        sf::Transformable::setPosition(rand()%width, 0);
    }else if (_type == normal)
    {
        this->setEntityTexture("resources/image/shoot.png",534,612,57,43);
        this->setTexture(*(getTexture()));
        crashTexture1.loadFromFile("resources/image/shoot.png",sf::IntRect(267, 347, 57, 51));
        crashTexture2.loadFromFile("resources/image/shoot.png",sf::IntRect(873, 697, 57, 51));
        crashTexture3.loadFromFile("resources/image/shoot.png",sf::IntRect(930, 697, 57, 51));
        this->setSpeed(130);
        this->setHP(1);
        sf::Transformable::setPosition(rand()%width, 0);
    }else if (_type == boss)
    {
        this->setEntityTexture("resources/image/shoot.png",166,750,169,258);
        this->setTexture(*(getTexture()));
        crashTexture1.loadFromFile("resources/image/shoot.png",sf::IntRect(839, 748, 165, 260));
        crashTexture2.loadFromFile("resources/image/shoot.png",sf::IntRect(673, 748, 165, 260));
        crashTexture3.loadFromFile("resources/image/shoot.png",sf::IntRect(0, 747, 165, 260));
        this->setHP(50);
        this->setSpeed(100);
        sf::Transformable::setPosition(width/2-83, 0);
    }

    this->type = _type;

    buffer1.loadFromFile("resources/sound/enemy1_down.ogg");
    crashSound1.setBuffer(buffer1);
    buffer2.loadFromFile("resources/sound/enemy2_down.ogg");
    crashSound2.setBuffer(buffer2);
}

// // 敌机开火
void Enemy::fire()
{
    if (this->getType() == normal)
        enemyBullets.push_back(new Bullet(this->getPosition().x+27, this->getPosition().y, normal));
    else if (this->getType() == elite)
        enemyBullets.push_back(new Bullet(this->getPosition().x+34, this->getPosition().y, elite));
    else
        enemyBullets.push_back(new Bullet(this->getPosition().x+82, this->getPosition().y, boss));

}

// 返回敌机的子弹仓库
list<Bullet*> Enemy::getBullets()
{
    return enemyBullets;
}

// 当子弹超出屏幕或击中战斗机的时候，销毁子弹
void Enemy::destroyBullet(Bullet *&b)
{
    enemyBullets.remove(b);
}

void Enemy::crash()
{
    if (this->type == normal)
        crashSound1.play();
    else
        crashSound2.play();
}