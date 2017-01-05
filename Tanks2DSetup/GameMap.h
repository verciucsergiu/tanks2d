#pragma once
#include <SFML\Graphics.hpp>
#include <string.h>
#include <iostream>
using namespace sf;
using namespace std;

class GameMap
{
public:
	GameMap();
	~GameMap();
	enum tileType
	{
		ground, wall
	};
	int indexWallTileMap = 0;
	Vector2f wallAdress[9999];
	string wallTilePath;
	void addTile(float x, float y,tileType tile);
	void draw(RenderWindow &window);
	Texture wallTexture;
	Sprite wallSprite;
private:
	Sprite groundSprite;
	Texture groundTexture;
	
};

