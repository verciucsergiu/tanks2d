#include "Level.h"

Level::Level()
{
	testing = true;
	cameras.nrSquare = 0;
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
	player.update(deltaTime, window);
	Draw(window);
	CameraBehavior(window);
}

void Level::Draw(RenderWindow & window)
{
	tileMap.draw(window);
	player.draw(window);
	for (BulletsFired * current = bFiredFirst; current != nullptr; current = current->next)
	{
		current->bullet->Update(fixedDeltaTime, window);

		if (current->bullet->checkCollision())
		{
			eliminareBullet(current);
		}
	}
}



void Level::initPlayer()
{
	player.setRotationSpeed(350);
	player.setScale(1.3f, 1.3f);
	player.startPosition(300, 300);
	player.setBoxColliderOffset(2, 2);
}

void Level::CameraBehavior(RenderWindow &window)
{
	
	for (int i = 0; i < cameras.nrSquare; i++)
	{
		if (cameras.square[i].collision.contains(player.tankSprite.getPosition().x, player.tankSprite.getPosition().y))
		{
			followPlayer.setCenter(window.getSize().x / 2 + window.getSize().x * cameras.square[i].gridX, window.getSize().y / 2 + window.getSize().y * cameras.square[i].gridY);
		}
	}
	
	
	followPlayer.setSize(window.getSize().x, window.getSize().y);
	followPlayer.zoom(1);
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

void Level::GenerateMap(string fisier)
{
	//800 px width
	//576 px height
	ifstream fin(fisier);
	int mat[100][100];
	int rows, collumns;
	fin >> rows >> collumns;
	for (int row = 0; row < rows; row++)
	{
		for (int col = 0; col < collumns; col++)
		{
			fin >> mat[row][col];
		}
	}

	for (int row = 1; row < rows - 1; row++)
	{
		for (int col = 1; col < collumns -1; col++)
		{
			if (mat[row][col])
			{
				bool dreapta = mat[row][col + 1];
				bool stanga = mat[row][col - 1];
				bool sus = mat[row - 1][col];
				bool jos = mat[row + 1][col];
				mapGrid((row - 1) * 18, (col - 1) * 25, sus, jos, stanga, dreapta);
				if (mat[row][col] == 2)
				{
					createCamera(col - 1, row - 1);
				}
			}
		}
	}
	MapCollisions();
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
		player.addCollider(newSprite);
	}
}

void Level::createCamera(int x, int y)
{
	followPlayer.setCenter(400 + 800 * x, 288 + 576 * y);
	player.startPosition(400 + 800 * x, 288 + 576 * y);
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
