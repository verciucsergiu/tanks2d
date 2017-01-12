#pragma once
#include "SFML\Graphics.hpp"
#include <iostream>
#include <string>
#include "bullet.h"
using namespace sf;
using namespace std;

struct PosInSpace
{
	int gridX, gridY, x, y;
};
struct glont
{
	Sprite bulletSpr;
	float normalX, normalY;
};
struct Bullets
{
	glont bull[10]; 
	int nrOfBullets;
};
class Tower
{
public:
	Tower();
	~Tower();
	Sprite tunSprite;
	Sprite towerSprite;
	Texture tunTexture;
	Texture towerTexture;
	int health;
	int damage;
	void setPosition(int gridX, int gridY, int x, int y);
	void draw(RenderWindow &window);
	void takeDamage(int value);
	void setAlive(bool value);
	void update(float deltaTime, RenderWindow &window);
	void tankPosition(int gridX, int gridY, int x, int y);
	bool isAlive();
	void initalization();
	void urmaresteTank(RenderWindow &window);
	void fire(int targetX, int targetY);
	void setTankSprite(Sprite tank);
	bool isHit();
	void eliminareBullet(int pos);
private:
	Sprite bulletTexture;
	bool alive;
	PosInSpace tankPos, towerPos;

	void resetBullets();
	Bullets bullets;
	bool canFire;
	float fireDelay;
	float currentDelay;
	float time;
	Texture bulTexture;
	Sprite tankSprite;
	bool hit;
	float speed;
};

