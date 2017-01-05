#pragma once
#include "SFML\Graphics.hpp"
#include <iostream>
#include <fstream>
#include <cctype>
#include <string>
#include "Player.h"
#include "GameMap.h"

using namespace std;
using namespace sf;

struct BulletsFired
{
	bullet *bullet;
	BulletsFired *next;
};

class Game
{
public:
	Game();
	~Game();
private:
	void Draw(RenderWindow &window);
	void CreateCamera(float zoom);
	void CameraBehavior();
	void MapCollisions();
	void AddCollision(Sprite sprite);

	View followPlayer;
	Clock clock;
	float deltaTime;
	RenderWindow window;
	Player player;
	GameMap tileMap;

	BulletsFired *bFiredFirst;
	BulletsFired *bFiredLast;
	void addBullets(bullet * target);
	void resetBullets();
	void updateBullets();
	void setFireDelay(float value);
	float fireDelay;

	void MapGenerator();
};

