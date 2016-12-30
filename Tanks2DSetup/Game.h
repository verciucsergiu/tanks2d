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

class Game
{
public:
	Game();
	~Game();
private:
	void Draw(RenderWindow &window);
	void CreateCamera();
	void CameraBehavior();
	void MapCollisions();
	void AddCollision(Sprite sprite);

	View followPlayer;
	Clock clock;
	RenderWindow window;
	Player player;
	GameMap tileMap;
};

