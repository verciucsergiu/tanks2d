#include "EndGame.h"



EndGame::EndGame()
{
	alive = true;
	if (!finishTexture.loadFromFile("sprites/finish.png"))
	{

	}
	finishSprite.setTexture(finishTexture);
}


EndGame::~EndGame()
{
}

void EndGame::draw(RenderWindow & window)
{
	window.draw(finishSprite);
}

void EndGame::setPosition(int gridX, int gridY, int x, int y)
{
	float xPos = 800 * gridX + x;
	float yPos = 576 * gridY + y;
	finishSprite.setPosition(xPos, yPos);
}

void EndGame::takeDamage(int value)
{
	if (alive)
	{
		health -= value;
		if (health <= 0)
		{
			alive = false;
		}
	}
}

void EndGame::setPlay()
{
	alive = true;
}

bool EndGame::isAlive()
{
	return alive;
}
