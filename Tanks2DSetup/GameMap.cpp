#include "GameMap.h"

enum tileType
{
	ground,wall
};
GameMap::GameMap()
{
	if (!groundTexture.loadFromFile("sprites/tile_ground.png"))
	{
		cout << "Error loading ground!\n";
	}
	if (!wallTexture.loadFromFile("sprites/tile_wall.png"))
	{
		cout << "Error loading wall!\n";
	}
	groundSprite.setTexture(groundTexture);
	wallSprite.setTexture(wallTexture);
}

GameMap::~GameMap()
{
}
void GameMap::draw(RenderWindow &window)
{
	for (int i = -15; i < 35; i++)
	{
		for (int  j = -15; j < 35; j++)
		{
			groundSprite.setPosition(i * 32, j * 32);
			window.draw(groundSprite);
		}
	}
	for (int i = 0; i < indexWallTileMap; i++)
	{
		wallSprite.setPosition(wallAdress[i].x,wallAdress[i].y);
		window.draw(wallSprite);
	}
}
void GameMap::addTile(int x, int y, tileType tile)
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
