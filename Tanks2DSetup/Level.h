#pragma once
#include "SFML\Graphics.hpp"
#include <iostream>
#include <fstream>
#include <cctype>
#include <string>
#include "Player.h"
#include "GameMap.h"
#include "bullet.h"
#include "EndGame.h"
using namespace std;
using namespace sf;

struct BulletsFired
{
	bullet *bullet;
	BulletsFired *next;
};
struct CameraGrid
{
	FloatRect collision;
	int gridX;
	int gridY;
};
struct ArrayCameraGrid
{
	CameraGrid square[100];
	int nrSquare;
};
struct Stats
{
	int health;
	int damage;
	int currentLevel;
	float speed;
	float bulletSpeed;
};
class Level
{
public:
	Level();
	~Level();

	void Create();
	void Update(float deltaTime, RenderWindow &window);
	

	void initPlayer();

	float fixedDeltaTime;
	Player player;
	GameMap tileMap;

	View followPlayer;
	void CameraBehavior(RenderWindow &window);

	void addBullets(bullet * target);
	void resetBullets();
	void setFireDelay(float value);
	void setNewLevel();
	void GenerateMap(string fisier);
	void setPlayerStats(Stats value);
	bool gameEnd();
private:
	float currentDelay;
	bool canFire;
	float fireDelay;
	void addBulletCollision(bullet &target);
	void eliminareBullet(BulletsFired *target);
	BulletsFired *bFiredFirst;
	BulletsFired *bFiredLast;
	void Draw(RenderWindow &window);
	void mapGrid(int startX, int startY, bool sus, bool jos, bool stanga, bool dreapta);
	void MapCollisions();
	ArrayCameraGrid cameras;


	void createCamera(int x,int y);
	void createFinish(int x, int y);
	EndGame endTheGame;
	bool testing;
	
	Vector2i playerStartingPos;
};

