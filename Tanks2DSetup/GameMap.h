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
	Vector2i wallAdress[1000];
	string groundTilePath;
	string wallTilePath;
	void addTile(int x, int y,tileType tile);
	void draw(RenderWindow &window);
	Texture wallTexture;
private:
	Sprite groundSprite;
	Texture groundTexture;
	Sprite wallSprite;

};

