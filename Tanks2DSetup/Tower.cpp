#include "Tower.h"



Tower::Tower()
{
	if (!towerTexture.loadFromFile("sprites/tower.png")) {
	}
	towerSprite.setTexture(towerTexture);

}


Tower::~Tower()
{
}
void Tower::draw(RenderWindow &window)
{
	window.draw(towerSprite);
}

void Tower::setPosition(int gridX, int gridY, int x, int y)
{
	float posX = 800 * gridX + x;
	float posY = 576 * gridY + y;
	towerSprite.setPosition(posX, posY);
}
