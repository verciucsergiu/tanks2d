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
#include "objectsOnMap.h"
#include "Tower.h"

using namespace std;
using namespace sf;


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

struct objectOnMapList
{
	objectsOnMap obj[200];
	int nrObjects;
};
struct towerList
{
	Tower list[20];
	int nrTowers;
};
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
	void setPlay();

	void setPause(bool value);
	bool isPause();
	Vector2i getCameraPos();
private:

	Collider *collFirst;
	Collider *collLast;
	void resetCollider();
	Collider2D *c2DFirst;
	Collider2D *c2DLast;
	
	float currentDelay;
	bool canFire;
	float fireDelay;
	void addBulletCollision();
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
	objectOnMapList objects;

	towerList towers;
	PosInSpace tankPos;

	int mapMap[25][25];
	int rows, collumns;

	bool pause;
};

