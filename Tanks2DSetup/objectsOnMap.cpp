#include "objectsOnMap.h"



objectsOnMap::objectsOnMap()
{
}


objectsOnMap::~objectsOnMap()
{
}

void objectsOnMap::create(int gridX, int gridY, int x, int y, int type)
{
	switch (type)
	{
	case 0:
		if (!objectTexture.loadFromFile("sprites/treelarge.png"));
		{

		}
		break;
	case 1:
		if (!objectTexture.loadFromFile("sprites/treesmall.png"));
		{

		}
		break;
	case 2:
		if (!objectTexture.loadFromFile("sprites/barrelred_side.png"));
		{

		}
		break;
	case 3:
		if (!objectTexture.loadFromFile("sprites/barrelgrey_side.png"));
		{

		}
		break;
	default:
		break;
	}
	float xPos = 800 * gridX + x;
	float yPos = 576 * gridY + y;
	objectSprite.setTexture(objectTexture);
	objectSprite.setPosition(xPos, yPos);
}

void objectsOnMap::draw(RenderWindow & window)
{
	window.draw(objectSprite);
}
