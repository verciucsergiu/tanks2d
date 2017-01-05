#include "Game.h"

Game::Game()
{
	bool canFire = true;
	float currentDelay = 0;

	window.create(VideoMode(800, 574), "TANKS 2D", Style::Titlebar | Style::Close);

	resetBullets();

	CreateCamera(0.65f);

	setFireDelay(.2f);

	player.setSpeed(150);
	player.setRotationSpeed(350);
	player.setScale(1.3f, 1.3f);
	player.startPosition(100, 100);
	player.setBoxColliderOffset(2, 2);
	
	MapGenerator();

	MapCollisions();

	while (window.isOpen())
	{
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
			{
				window.close();
			}
		}
		Time time = clock.getElapsedTime();
		deltaTime = time.asSeconds();

		player.update(deltaTime, window);
		clock.restart().asSeconds();
		
		Color clearColor(150, 150, 150, 255);
		window.clear(clearColor);
		

		/*bullet handle*/

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
		updateBullets();
		Draw(window);
	
		//DEBUGING
		Vector2f tankpos = player.tankSprite.getPosition();
		Font font;
		font.loadFromFile("sansation.ttf");
		String fps = "FPS: " + to_string((int)(1 / time.asSeconds()));
		Text fpsT(fps, font);
		fpsT.setCharacterSize(15);
		fpsT.setPosition(window.getView().getCenter().x - window.getView().getSize().x / 2, window.getView().getCenter().y - window.getView().getSize().y / 2);
		window.draw(fpsT);

		CameraBehavior();
		
		window.display();
	}
}
Game::~Game()
{
	
}
void Game::Draw(RenderWindow & window)
{
	tileMap.draw(window);
	player.draw(window);
}
void Game::CreateCamera(float zoom)
{
	followPlayer.setCenter(0, 0);
	followPlayer.setSize(window.getSize().x, window.getSize().y);
	followPlayer.zoom(zoom);
	window.setView(followPlayer);
}

void Game::CameraBehavior()
{
	followPlayer.setCenter(250, 200);
	window.setView(followPlayer);
}

void Game::MapCollisions()
{
	//collision
	for (int i = 0; i < tileMap.indexWallTileMap; i++)
	{
		Sprite newSprite;
		newSprite.setTexture(tileMap.wallTexture);
		newSprite.setPosition(tileMap.wallAdress[i].x, tileMap.wallAdress[i].y);
		player.addCollider(newSprite);
	}
}

void Game::AddCollision(Sprite sprite)
{
	player.addCollider(sprite);
}

void Game::addBullets(bullet * target)
{
	if (bFiredFirst != nullptr && bFiredLast !=nullptr)
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

void Game::resetBullets()
{
	bFiredFirst = nullptr;
	bFiredLast = nullptr;
}
void Game::updateBullets()
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
void Game::eliminareBullet(BulletsFired * target)
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

void Game::setFireDelay(float value)
{
	fireDelay = value;
}

void Game::addBulletCollision(bullet & target)
{
	for (int i = 0; i < tileMap.indexWallTileMap; i++)
	{
		Sprite newSprite;
		newSprite.setTexture(tileMap.wallTexture);
		newSprite.setPosition(tileMap.wallAdress[i].x, tileMap.wallAdress[i].y);
		target.addCollider(newSprite);
	}
}

void Game::MapGenerator()
{
	int walls = 12;
	for (int i = 0; i < walls; i++)
	{
		tileMap.addTile(i, 0, GameMap::tileType::wall);
		tileMap.addTile(0, i, GameMap::tileType::wall);
		tileMap.addTile(walls, i, GameMap::tileType::wall);
		tileMap.addTile(i, walls, GameMap::tileType::wall);
	}
	tileMap.addTile(walls, walls, GameMap::tileType::wall);
	tileMap.addTile(6, 6, GameMap::tileType::wall);
	tileMap.addTile(6, 7, GameMap::tileType::wall);
	tileMap.addTile(7, 7, GameMap::tileType::wall);
	tileMap.addTile(7, 6, GameMap::tileType::wall);
}
