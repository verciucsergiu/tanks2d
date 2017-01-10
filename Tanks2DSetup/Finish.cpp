#include "Finish.h"



Finish::Finish()
{
	alive = true;
	if (!finishTexture.loadFromFile("sprites/finish.png"))
	{

	}
	finishSprite.setTexture(finishTexture);
}


Finish::~Finish()
{

}

void Finish::draw(RenderWindow & window)
{
	window.draw(finishSprite);
}

void Finish::setPosition(int gridX, int gridY,int x,int y)
{
	float xPos = 800 * gridX + x;
	float yPos = 576 * gridY + y;
	finishSprite.setPosition(xPos, yPos);
}

void Finish::takeDamage(int value)
{
	if (alive)
	{
		health -= value;
		cout << value << " " << health << '\n';
		if (health <= 0)
		{

			alive = false;
		}
	}
	
}

bool Finish::isAlive()
{
	return alive;
}
