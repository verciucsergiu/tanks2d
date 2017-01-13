#include "GameMap.h"

GameMap::GameMap()
{
	
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
void GameMap::setWallString(string value)
{
	wallString = value;
}
void GameMap::create()
{
	if (!wallTexture.loadFromFile(wallString)) //Schimbat numele imaginii
	{
		cout << "Error loading wall!\n";
	}
	wallSprite.setTexture(wallTexture);
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
