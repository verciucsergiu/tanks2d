#include "Tower.h"



Tower::Tower()
{
	
}


Tower::~Tower()
{
}


void Tower::takeDamage(int value)
{
	if (alive)
	{
		health -= value;
		if (health <=0)
		{
			alive = false;
		}
	}
}

void Tower::setAlive(bool value)
{
	alive = value;
}

void Tower::update(float deltaTime, RenderWindow & window)
{
	draw(window);
	time = deltaTime;
	if (tankPos.gridX == towerPos.gridX && tankPos.gridY == towerPos.gridY)
	{
		if (canFire)
		{
			canFire = false;
			bullet *newBull;
			newBull->create();
			newBull->setStartPosition(towerPos.x, towerPos.y);
			newBull->setTarget(tankPos.x, tankPos.y);
			Vector2i target(tankPos.x, tankPos.y);
			newBull->setBulletRotation(target, window);
			addBullets(newBull);
		}
		else
		{
			if (currentDelay>=0)
			{
				currentDelay -= deltaTime;
			}
			else
			{
				currentDelay = fireDelay;
				canFire = true;
			}
		}
	}
}
void Tower::draw(RenderWindow &window)
{
	window.draw(towerSprite);
	window.draw(tunSprite);
	for (BulletsFired * current = bFiredFirst; current != nullptr; current = current->next)
	{
		current->bullet->Update(time, window);
	}
}
void Tower::tankPosition(int gridX, int gridY, int x, int y)
{
	tankPos.gridX = gridX;
	tankPos.gridY = gridY;
	tankPos.x = x;
	tankPos.y = y;
}

bool Tower::isAlive()
{
	return alive;
}

void Tower::initalization()
{
	if (!towerTexture.loadFromFile("sprites/tower_base.png")) {
	}
	towerSprite.setTexture(towerTexture);
	if (!tunTexture.loadFromFile("sprites/tower_tun.png")) {
	}
	tunSprite.setTexture(tunTexture);
	//towerSprite.setOrigin(towerSprite.getGlobalBounds().height / 2, towerSprite.getGlobalBounds().width / 2);
	//tunSprite.setOrigin(tunSprite.getGlobalBounds().height / 2, tunSprite.getGlobalBounds().width / 2);
	canFire = true;
	fireDelay = .35f;
	currentDelay = fireDelay;
	resetBullets();
}

void Tower::addBullets(bullet * target)
{
	if (bFiredFirst != nullptr && bFiredLast != nullptr)
	{
		BulletsFired *add = new BulletsFired;
		add->bullet = target;
		add->next = nullptr;
		bFiredLast->next = add;
		bFiredLast = add;
	}
	else
	{
		BulletsFired *add = new BulletsFired;
		add->bullet = target;
		add->next = nullptr;
		bFiredFirst = add;
		bFiredLast = bFiredFirst;
	}
}

void Tower::resetBullets()
{
	bFiredFirst = nullptr;
	bFiredLast = nullptr;
}

void Tower::setPosition(int gridX, int gridY, int x, int y)
{
	float posX = 800 * gridX + x;
	float posY = 576 * gridY + y;
	towerPos.gridX = gridX;
	towerPos.gridY = gridY;
	towerPos.x = x;
	towerPos.y = y;
	towerSprite.setPosition(posX, posY);
	tunSprite.setPosition(posX, posY);
}
