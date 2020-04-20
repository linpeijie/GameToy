#ifndef ENTITY_H
#define ENTITY_H
#include <iostream>
#include <vector>
#include <list>
#include <string>
#include <math.h>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>

#define width 480
#define hight 800
#define boss 101
#define hero 3
#define elite 2
#define normal 1

using namespace std;

class Entity:public sf::Sprite
{
public:
	Entity();
	Entity(int _hp);

	void         setEntityTexture(const string filePath,int x,int y,int sizex,int sizey);
	sf::Texture* getTexture();
	void         setSpeed(int speed);
    float        getSpeed();
	void         setHP(int hp);
    int          getHP();
	void         hurted();
	bool         isAlive();

private:
	sf::Texture  mTexture;
	float        speed;
	int          HP;

};

#endif