#include "Tower.h"



Tower::Tower()
{
	resetBullets();
	hit = false;
	if (!bulTexture.loadFromFile("sprites/bullet.png"))
	{

	}
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
	hit = false;
	for (int i = 0; i < bullets.nrOfBullets; i++)
	{
		bullets.bull[i].bulletSpr.move(bullets.bull[i].normalX * deltaTime * speed, bullets.bull[i].normalY * deltaTime * speed);
		bullets.bull[i].bulletSpr.setTexture(bulTexture);
		hit = false;
		if (tankSprite.getGlobalBounds().contains(bullets.bull[i].bulletSpr.getPosition().x, bullets.bull[i].bulletSpr.getPosition().y))
		{
			eliminareBullet(i);
			hit = true;
		}
		Vector2f currentpos = bullets.bull[i].bulletSpr.getPosition();
		FloatRect camera(towerPos.gridX * 800 + 32, towerPos.gridY * 576, 768, 544);
		if (!camera.contains(currentpos.x,currentpos.y))
		{
			eliminareBullet(i);
		}
		window.draw(bullets.bull[i].bulletSpr);
	}
	draw(window);
	if (tankPos.gridX == towerPos.gridX && tankPos.gridY == towerPos.gridY && alive)
	{
		if (canFire)
		{
			fire(tankPos.x, tankPos.y);
			canFire = false;
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
	if (alive)
	{
		towerSprite.setTexture(towerTexture);
		window.draw(towerSprite);
		window.draw(tunSprite);
		urmaresteTank(window);
	}
	else
	{
		towerSprite.setTexture(towerTextureDestroy);
		window.draw(towerSprite);
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
	if (!towerTextureDestroy.loadFromFile("sprites/tower_base_destroy.png")) {
	}
	tunSprite.setTexture(tunTexture);
	float x = tunSprite.getOrigin().x + 32;
	float y = tunSprite.getOrigin().y + 16;
	tunSprite.setOrigin(x, y);
	canFire = true;
	fireDelay = .5f;
	currentDelay = fireDelay;
	resetBullets();
	speed = 650;
	health = 350;
}

void Tower::urmaresteTank(RenderWindow &window)
{
	Vector2f currentPos = tunSprite.getPosition();

	const float PI = 3.14159265;
	float dx = currentPos.x - tankPos.x;
	float dy = currentPos.y - tankPos.y;
	float tunRotation = (atan2(dy, dx)) * 180 / PI;
	tunSprite.setRotation(tunRotation);
}

void Tower::fire(int targetX, int targetY)
{
	if (bullets.nrOfBullets < 8)
	{
		float x = targetX - tunSprite.getPosition().x;
		float y = targetY - tunSprite.getPosition().y;
		float normalize = sqrt(x*x + y*y);
		x = x / normalize;
		y = y / normalize;
		bullets.bull[bullets.nrOfBullets].bulletSpr.setPosition(tunSprite.getPosition().x, tunSprite.getPosition().y);
		bullets.bull[bullets.nrOfBullets].normalX = x;
		bullets.bull[bullets.nrOfBullets].normalY = y;
		bullets.nrOfBullets++;
	}
}

void Tower::setTankSprite(Sprite tank)
{
	tankSprite = tank;
}

bool Tower::isHit()
{
	return hit;
}

void Tower::eliminareBullet(int pos)
{
	if (bullets.nrOfBullets>0)
	{
		for (int i = pos; i < bullets.nrOfBullets - 1; i++)
		{
			bullets.bull[i] = bullets.bull[i + 1];
		}
	}
	bullets.nrOfBullets--;
}


void Tower::resetBullets()
{
	bullets.nrOfBullets = 0;
}

void Tower::setPosition(int gridX, int gridY, int x, int y)
{
	float posX = 800 * gridX + x;
	float posY = 576 * gridY + y;
	towerPos.gridX = gridX;
	towerPos.gridY = gridY;
	towerPos.x = posX;
	towerPos.y = posY;
	towerSprite.setPosition(posX, posY);
	tunSprite.setPosition(posX+11, posY+16);
}
