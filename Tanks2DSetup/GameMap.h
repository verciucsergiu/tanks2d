#pragma once
#include <SFML\Graphics.hpp>
#include <string.h>
#include <iostream>
using namespace sf;
using namespace std;


#define MAX_WALLS 1000
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
	Sprite wallCollision[MAX_WALLS];
	Texture wallTexture;
private:
	Sprite groundSprite;
	Texture groundTexture;
	Sprite wallSprite;

};

