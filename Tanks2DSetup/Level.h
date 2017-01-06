#pragma once
#include "SFML\Graphics.hpp"
#include <iostream>
#include <fstream>
#include <cctype>
#include <string>
#include "Player.h"
#include "GameMap.h"
#include "bullet.h"

using namespace std;
using namespace sf;

struct BulletsFired
{
	bullet *bullet;
	BulletsFired *next;
};
class Level
{
public:
	Level();
	~Level();

	void Update(float deltaTime, RenderWindow &window);
	void Draw(RenderWindow &window);

	void initPlayer();

	float deltaTime;
	Player player;
	GameMap tileMap;

	BulletsFired *bFiredFirst;
	BulletsFired *bFiredLast;
	void addBullets(bullet * target);
	void resetBullets();
	void updateBullets(RenderWindow &window);
	void setFireDelay(float value);
	float fireDelay;
	void addBulletCollision(bullet &target);
	void eliminareBullet(BulletsFired *target);

	void MapGenerator();
	void MapCollisions();


private:
	float currentDelay;
	bool canFire;
};

