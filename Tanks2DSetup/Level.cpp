#include "Level.h"
#include "bullet.h"

Level::Level()
{
	testing = true;
	cameras.nrSquare = 0;
	resetCollider();
}

Level::~Level()
{

}

void Level::Create()
{
	
	currentDelay = 0;
	canFire = true;
	resetBullets();
	initPlayer();
	fireDelay = .25f;
	
}

void Level::Update(float deltaTime, RenderWindow & window)
{
	fixedDeltaTime = deltaTime;
	if (Mouse::isButtonPressed(Mouse::Left) && canFire && !isPause())
	{
		bullet *fire = new bullet;
		fire->create();
		fire->setStartPosition(player.barrelSprite.getPosition().x, player.barrelSprite.getPosition().y);
		fire->setBulletRotation(Mouse::getPosition(window), window);
		Vector2f targetPos = window.mapPixelToCoords(Mouse::getPosition(window));
		fire->setSpeed(1000);
		fire->setTarget(targetPos.x, targetPos.y);
		fire->setColliders(c2DFirst, c2DLast);
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
	player.update(deltaTime, window);
	Draw(window);
	player.setCollider(collFirst, collLast);
	CameraBehavior(window);
}

void Level::Draw(RenderWindow & window)
{
	tileMap.draw(window);
	player.draw(window);
	endTheGame.draw(window);
	for (BulletsFired * current = bFiredFirst; current != nullptr; current = current->next)
	{
		current->bullet->Update(fixedDeltaTime, window);
		current->bullet->setColliders(c2DFirst, c2DLast);
		if (current->bullet->checkCollision())
		{
			if (current->bullet->collisionType == 1)
			{
				endTheGame.takeDamage(player.damage);
			}
			eliminareBullet(current);
		}
	}
	for (int i = 0; i < objects.nrObjects; i++)
	{
		objects.obj[i].draw(window);
	}
	for (int i = 0; i < towers.nrTowers; i++)
	{
		towers.list[i].update(fixedDeltaTime, window);
		towers.list[i].tankPosition(tankPos.gridX, tankPos.gridY, player.tankSprite.getPosition().x, player.tankSprite.getPosition().y);
		towers.list[i].setTankSprite(player.tankSprite);
		if (towers.list[i].isHit())
		{
			player.takeDamage(50);
		}
	}
}



void Level::initPlayer()
{
	player.setRotationSpeed(350);
	player.setScale(1.3f, 1.3f);
	player.setBoxColliderOffset(2, 2);
}

void Level::CameraBehavior(RenderWindow &window)
{
	
	for (int i = 0; i < cameras.nrSquare; i++)
	{
		if (cameras.square[i].collision.contains(player.tankSprite.getPosition().x, player.tankSprite.getPosition().y))
		{
			followPlayer.setCenter(window.getSize().x / 2 + window.getSize().x * cameras.square[i].gridX, window.getSize().y / 2 + window.getSize().y * cameras.square[i].gridY);
			tankPos.gridX = cameras.square[i].gridX;
			tankPos.gridY = cameras.square[i].gridY;
		}
	}
	window.setView(followPlayer);
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

void Level::setFireDelay(float value)
{
	fireDelay = value;
}

void Level::addBulletCollision()
{
	for (int i = 0; i < tileMap.indexWallTileMap; i++)
	{
		Sprite newSprite;
		newSprite.setTexture(tileMap.wallTexture);
		newSprite.setPosition(tileMap.wallAdress[i].x, tileMap.wallAdress[i].y);
		if (c2DFirst != nullptr && c2DLast != nullptr)
		{
			Collider2D * add = new Collider2D;
			add->target = newSprite;
			add->role = 0;
			add->next = nullptr;
			c2DLast->next = add;
			c2DLast = add;
		}
		else
		{
			Collider2D * add = new Collider2D;
			add->target = newSprite;
			add->role = 0;
			add->next = nullptr;
			c2DFirst = add;
			c2DLast = c2DFirst;
		}
	}
	Sprite newSprite;
	newSprite.setTexture(endTheGame.finishTexture);
	newSprite.setPosition(endTheGame.finishSprite.getPosition());
	if (c2DFirst != nullptr && c2DLast != nullptr)
	{
		Collider2D * add = new Collider2D;
		add->target = newSprite;
		add->role = 1;
		add->next = nullptr;
		c2DLast->next = add;
		c2DLast = add;
	}
	else
	{
		Collider2D * add = new Collider2D;
		add->target = newSprite;
		add->role = 1;
		add->next = nullptr;
		c2DFirst = add;
		c2DLast = c2DFirst;
	}
	for (int i = 0; i < objects.nrObjects; i++)
	{
		Sprite newSprite;
		newSprite.setTexture(objects.obj[i].objectTexture);
		newSprite.setPosition(objects.obj[i].objectSprite.getPosition());
		if (c2DFirst != nullptr && c2DLast != nullptr)
		{
			Collider2D * add = new Collider2D;
			add->target = newSprite;
			add->role = 0;
			add->next = nullptr;
			c2DLast->next = add;
			c2DLast = add;
		}
		else
		{
			Collider2D * add = new Collider2D;
			add->target = newSprite;
			add->role = 0;
			add->next = nullptr;
			c2DFirst = add;
			c2DLast = c2DFirst;
		}
	}
	for (int i = 0; i < towers.nrTowers; i++)
	{
		Sprite newSprite;
		newSprite.setTexture(towers.list[i].towerTexture);
		newSprite.setPosition(towers.list[i].towerSprite.getPosition());
		if (c2DFirst != nullptr && c2DLast != nullptr)
		{
			Collider2D * add = new Collider2D;
			add->target = newSprite;
			add->role = 0;
			add->next = nullptr;
			c2DLast->next = add;
			c2DLast = add;
		}
		else
		{
			Collider2D * add = new Collider2D;
			add->target = newSprite;
			add->role = 0;
			add->next = nullptr;
			c2DFirst = add;
			c2DLast = c2DFirst;
		}
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

void Level::GenerateMap(string fisier)
{
	//800 px width
	//576 px height
	ifstream fin(fisier);
	fin >> rows >> collumns;
	for (int row = 0; row < rows; row++)
	{
		for (int col = 0; col < collumns; col++)
		{
			fin >> mapMap[row][col];
		}
	}

	for (int row = 1; row < rows - 1; row++)
	{
		for (int col = 1; col < collumns -1; col++)
		{
			if (mapMap[row][col])
			{
				bool dreapta = mapMap[row][col + 1];
				bool stanga = mapMap[row][col - 1];
				bool sus = mapMap[row - 1][col];
				bool jos = mapMap[row + 1][col];
				mapGrid((row - 1) * 18, (col - 1) * 25, sus, jos, stanga, dreapta);
				if (mapMap[row][col] == 2)
				{
					tankPos.gridX = col - 1;
					tankPos.gridY = row - 1;
					createCamera(col - 1, row - 1);
				}
				if (mapMap[row][col] == 3)
				{
					createFinish(col - 1, row - 1);
				}
			}
		}
	}
	
	int nrObjects;
	fin >> nrObjects;
	for (int index = 0; index < nrObjects; index++)
	{
		int gridX, gridY, x, y,type;
		fin >> gridX >> gridY >> x >> y >> type;
		objects.obj[index].create(gridX, gridY, x, y, type);
	}
	objects.nrObjects = nrObjects;
	int nrTower;
	fin >> nrTower;
	for (int i = 0; i < nrTower; i++)
	{
		int gridX, gridY, x, y;
		fin >> gridX >> gridY >> x >> y;
		towers.list[i].initalization();
		towers.list[i].setAlive(true);
		towers.list[i].setPosition(gridX, gridY, x, y);
	}
	towers.nrTowers = nrTower;
	MapCollisions();
	addBulletCollision();
}
void Level::mapGrid(int startX, int startY, bool sus, bool jos, bool stanga, bool dreapta)
{
	int x = startY;
	int y = startX;
	
	for (int i = 0; i < 18; i++)
	{
		bool canSt = true;
		if (stanga && (i >= 9 && i <= 10))
		{
			canSt = false;
		}
		bool canDr = true;
		if (dreapta && (i >= 9 && i <= 10))
		{
			canDr = false;
		}
		if (canSt)
		{
			tileMap.addTile(x, i + y, tileType::wall);
		}
		else
		{
			cameras.square[cameras.nrSquare].collision.height = 32;
			cameras.square[cameras.nrSquare].collision.width = 32;
			cameras.square[cameras.nrSquare].collision.top = (i + y) * 32;
			cameras.square[cameras.nrSquare].collision.left = x * 32;
			cameras.square[cameras.nrSquare].gridX = x / 25;
			cameras.square[cameras.nrSquare++].gridY = y / 18;
		}
		if (canDr)
		{
			tileMap.addTile(24 + x, i + y, tileType::wall);
		}
		else
		{
			cameras.square[cameras.nrSquare].collision.height = 32;
			cameras.square[cameras.nrSquare].collision.width = 32;
			cameras.square[cameras.nrSquare].collision.top = (i + y) * 32;
			cameras.square[cameras.nrSquare].collision.left = (24 + x) * 32;
			cameras.square[cameras.nrSquare].gridX = x / 25;
			cameras.square[cameras.nrSquare++].gridY = y / 18;
		}
		
	}
	for (int i = 0; i < 25; i++)
	{
		bool canJos = true;
		if (jos && i >= 10 && i <= 12)
		{
			canJos = false;
		}
		bool canSus = true;
		if (sus && i >= 10 && i <= 12)
		{
			canSus = false;
		}
		if (canSus)
		{
			tileMap.addTile(i + x, y, tileType::wall);
		}
		else
		{
			cameras.square[cameras.nrSquare].collision.height = 32;
			cameras.square[cameras.nrSquare].collision.width = 32;
			cameras.square[cameras.nrSquare].collision.top = y * 32;
			cameras.square[cameras.nrSquare].collision.left = (i + x) * 32;
			cameras.square[cameras.nrSquare].gridX = x / 25;
			cameras.square[cameras.nrSquare++].gridY = y / 18;
		}
		if (canJos)
		{
			tileMap.addTile(i + x, 17 + y, tileType::wall);
		}
		else
		{
			cameras.square[cameras.nrSquare].collision.height = 32;
			cameras.square[cameras.nrSquare].collision.width = 32;
			cameras.square[cameras.nrSquare].collision.top = (17 + y) * 32;
			cameras.square[cameras.nrSquare].collision.left = (i + x) * 32;
			cameras.square[cameras.nrSquare].gridX = x / 25;
			cameras.square[cameras.nrSquare++].gridY = y / 18;
		}
	}
}

void Level::MapCollisions()
{
	for (int i = 0; i < tileMap.indexWallTileMap; i++)
	{
		Sprite newSprite;
		newSprite.setTexture(tileMap.wallTexture);
		newSprite.setPosition(tileMap.wallAdress[i].x, tileMap.wallAdress[i].y);
		if (collFirst != nullptr && collLast != nullptr)
		{
			Collider * add = new Collider;
			add->target = newSprite;
			add->next = nullptr;
			collLast->next = add;
			collLast = add;
		}
		else
		{
			Collider * add = new Collider;
			add->target = newSprite;
			add->next = nullptr;
			collFirst = add;
			collLast = collFirst;
		}
	}
	Sprite newSprite;
	newSprite.setTexture(endTheGame.finishTexture);
	newSprite.setPosition(endTheGame.finishSprite.getPosition());
	if (collFirst != nullptr && collLast != nullptr)
	{
		Collider * add = new Collider;
		add->target = newSprite;
		add->next = nullptr;
		collLast->next = add;
		collLast = add;
	}
	else
	{
		Collider * add = new Collider;
		add->target = newSprite;
		add->next = nullptr;
		collFirst = add;
		collLast = collFirst;
	}
	for (int i = 0; i < objects.nrObjects; i++)
	{
		Sprite newSprite;
		newSprite.setTexture(objects.obj[i].objectTexture);
		newSprite.setPosition(objects.obj[i].objectSprite.getPosition());
		if (collFirst != nullptr && collLast != nullptr)
		{
			Collider * add = new Collider;
			add->target = newSprite;
			add->next = nullptr;
			collLast->next = add;
			collLast = add;
		}
		else
		{
			Collider * add = new Collider;
			add->target = newSprite;
			add->next = nullptr;
			collFirst = add;
			collLast = collFirst;
		}
	}
	for (int i = 0; i < towers.nrTowers; i++)
	{
		Sprite newSprite;
		newSprite.setTexture(towers.list[i].towerTexture);
		newSprite.setPosition(towers.list[i].towerSprite.getPosition());
		if (collFirst != nullptr && collLast != nullptr)
		{
			Collider * add = new Collider;
			add->target = newSprite;
			add->next = nullptr;
			collLast->next = add;
			collLast = add;
		}
		else
		{
			Collider * add = new Collider;
			add->target = newSprite;
			add->next = nullptr;
			collFirst = add;
			collLast = collFirst;
		}
	}
}

void Level::createCamera(int x, int y)
{
	followPlayer.setCenter(400 + 800 * x, 288 + 576 * y);
	player.startPosition(400 + 800 * x, 288 + 576 * y);
	playerStartingPos.x = 400 + 800 * x;
	playerStartingPos.y = 288 + 576 * y;
	followPlayer.setSize(800, 576);
	followPlayer.zoom(1);
}

void Level::createFinish(int x, int y)
{
	endTheGame.health = 100;
	endTheGame.setPosition(x, y, 400, 288);
}

void Level::setNewLevel()
{
	player.startPosition(playerStartingPos.x, playerStartingPos.y);
}

void Level::setPlayerStats(Stats value)
{
	player.damage = value.damage;
	player.health = value.health;
	player.setSpeed(value.speed);
	player.setRotationSpeed(400);
	player.setScale(1.3f, 1.3f);
	player.setBoxColliderOffset(2, 2);
}

bool Level::gameEnd()
{
	if (endTheGame.isAlive())
	{
		return false;
	}
	else
	{
		return true;
	}
	
}

void Level::setPlay()
{
	endTheGame.setPlay();
	player.setAlive(true);
	player.health = 100;
	for (int row = 0; row < rows; row++)
	{
		for (int col = 0; col < collumns; col++)
		{
			if (mapMap[row][col] == 2)
			{
				tankPos.gridX = col - 1;
				tankPos.gridY = row - 1;
				createCamera(col - 1, row - 1);
			}
		}
	}
}

void Level::setPause(bool value)
{
	pause = value;
}

bool Level::isPause()
{
	return pause;
}

Vector2i Level::getCameraPos()
{
	Vector2i pos;
	pos.x = followPlayer.getCenter().x;
	pos.y = followPlayer.getCenter().y;
	return pos;
}

void Level::resetCollider()
{
	
	collFirst = nullptr;
	collLast = nullptr;
	c2DFirst = nullptr;
	c2DLast = nullptr;
}
