#include "Level.h"

Level::Level()
{
	currentDelay = 0;
	canFire = true;
	resetBullets();
	MapGenerator();
	MapCollisions();
}

Level::~Level()
{

}

void Level::Update(float deltaTime, RenderWindow & window)
{

	player.update(deltaTime, window);

	if (Mouse::isButtonPressed(Mouse::Left) && canFire)
	{
		bullet *fire = new bullet;
		fire->create();
		fire->setStartPosition(player.barrelSprite.getPosition().x, player.barrelSprite.getPosition().y);
		Vector2f targetPos = window.mapPixelToCoords(Mouse::getPosition(window));
		fire->setSpeed(1000);
		fire->setTarget(targetPos.x, targetPos.y);
		addBulletCollision(*fire);
		addBullets(fire);

		canFire = false;
		currentDelay = fireDelay;
	}

	if (!canFire)
	{
		if (currentDelay > 0)
		{
			currentDelay -= deltaTime;
		}
		else
		{
			canFire = true;
		}
	}
}

void Level::Draw(RenderWindow & window)
{
	tileMap.draw(window);
	player.draw(window);
}

void Level::initPlayer()
{
	player.setSpeed(150);
	player.setRotationSpeed(350);
	player.setScale(1.3f, 1.3f);
	player.startPosition(100, 100);
	player.setBoxColliderOffset(2, 2);
}

void Level::addBullets(bullet * target)
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

void Level::resetBullets()
{
	bFiredFirst = nullptr;
	bFiredLast = nullptr;
}

void Level::updateBullets(RenderWindow &window)
{
	for (BulletsFired * current = bFiredFirst; current != nullptr; current = current->next)
	{
		current->bullet->Update(deltaTime, window);
		if (current->bullet->checkCollision())
		{
			eliminareBullet(current);
		}
	}
}

void Level::setFireDelay(float value)
{
	fireDelay = value;
}

void Level::addBulletCollision(bullet & target)
{
	for (int i = 0; i < tileMap.indexWallTileMap; i++)
	{
		Sprite newSprite;
		newSprite.setTexture(tileMap.wallTexture);
		newSprite.setPosition(tileMap.wallAdress[i].x, tileMap.wallAdress[i].y);
		target.addCollider(newSprite);
	}
}

void Level::eliminareBullet(BulletsFired * target)
{
	if (target == bFiredFirst)
	{
		BulletsFired *del = target;
		bFiredFirst = bFiredFirst->next;
	}
	else
	{
		BulletsFired *pointer = bFiredFirst;
		while (pointer->next != target)
		{
			pointer = pointer->next;
		}
		pointer->next = pointer->next->next;
	}
}

void Level::MapGenerator()
{
	for (int i = 0; i < 18; i++)
	{
		tileMap.addTile(0, i, GameMap::tileType::wall);
		tileMap.addTile(24, i, GameMap::tileType::wall);
	}
	for (int i = 0; i < 25; i++)
	{
		tileMap.addTile(i, 0, GameMap::tileType::wall);
		tileMap.addTile(i, 17, GameMap::tileType::wall);

	}
}

void Level::MapCollisions()
{
	for (int i = 0; i < tileMap.indexWallTileMap; i++)
	{
		Sprite newSprite;
		newSprite.setTexture(tileMap.wallTexture);
		newSprite.setPosition(tileMap.wallAdress[i].x, tileMap.wallAdress[i].y);
		player.addCollider(newSprite);
	}
}
