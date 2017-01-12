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

struct BulletsFired
{
	bullet *bullet;
	BulletsFired *next;
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
private:
	Sprite bulletTexture;
	bool alive;
	PosInSpace tankPos, towerPos;

	BulletsFired *bFiredFirst;
	BulletsFired *bFiredLast;

	void addBullets(bullet * target);
	void resetBullets();

	bool canFire;
	float fireDelay;
	float currentDelay;
	float time;
};

