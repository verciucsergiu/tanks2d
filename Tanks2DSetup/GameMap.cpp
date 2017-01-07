#include "GameMap.h"

GameMap::GameMap()
{
	if (!wallTexture.loadFromFile("sprites/tile_wall.png"))
	{
		cout << "Error loading wall!\n";
	}
	wallSprite.setTexture(wallTexture);
}

GameMap::~GameMap()
{
}
void GameMap::draw(RenderWindow &window)
{
	for (int i = 0; i < indexWallTileMap; i++)
	{
		wallSprite.setPosition(wallAdress[i].x,wallAdress[i].y);
		window.draw(wallSprite);
	}
}
void GameMap::addTile(float x, float y, tileType tile)
{
	switch (tile)
	{
	case ground:
		//groundSprite.setPosition(x,y);
		break;
	case wall:
		wallAdress[indexWallTileMap].x = x * 32;
		wallAdress[indexWallTileMap++].y = y * 32;
		break;
	}
}
