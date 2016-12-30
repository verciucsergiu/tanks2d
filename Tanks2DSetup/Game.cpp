#include "Game.h"

Game::Game()
{
	window.create(VideoMode(800, 574), "TANKS 2D", Style::Titlebar | Style::Close);
	window.setFramerateLimit(59);

	CreateCamera();

	player.create();
	player.setSpeed(150);
	player.setScale(1.3f, 1.3f);
	player.startPosition(-100, -20);
	player.setBoxColliderOffset(2, 2);
	
	int walls = 5;
	for (int i = 0; i < walls; i++)
	{
		tileMap.addTile(i, 0, GameMap::tileType::wall);
		tileMap.addTile(0, i, GameMap::tileType::wall);
		tileMap.addTile(walls, i, GameMap::tileType::wall);
		tileMap.addTile(i, walls, GameMap::tileType::wall);
	}
	tileMap.addTile(walls, walls, GameMap::tileType::wall);

	//Call after the walls were created and enemy spawned!;
	MapCollisions();
	//window
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
		player.update(time.asSeconds(), window);
		clock.restart().asSeconds();
		
		Color clearColor(150, 150, 150, 255);
		window.clear(clearColor);
		Draw(window);

		//DEBUGING
		Vector2f tankpos = player.tankSprite.getPosition();
		Font font;
		font.loadFromFile("sansation.ttf");
		String fps = "FPS: " + to_string((int)(1 / time.asSeconds()));
		Text fpsT(fps, font);
		fpsT.setCharacterSize(15);
		fpsT.setPosition(tankpos.x - 220, tankpos.y+10);
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

void Game::CreateCamera()
{
	followPlayer.setCenter(0, 0);
	followPlayer.setSize(800, 574);
	followPlayer.zoom(0.65f);
}

void Game::CameraBehavior()
{
	Vector2f tankpos = player.tankSprite.getPosition();

	//mouse lookForward
	followPlayer.setCenter(tankpos);
	window.setView(followPlayer);
}

void Game::MapCollisions()
{
	//collision
	for (int i = 0; i < tileMap.indexWallTileMap; i++)
	{
		player.collider.target[i].setTexture(tileMap.wallTexture);
		player.collider.target[i].setPosition(tileMap.wallAdress[i].x, tileMap.wallAdress[i].y);
		player.collider.numberOfTargets = tileMap.indexWallTileMap;
	}

	//enemy to add to player.collider.target[i]
	//metoda ineficienta de a verifica fiecare obstacol in parte dar mai putin cod de scris
}

void Game::AddCollision(Sprite sprite)
{
	player.collider.target[player.collider.numberOfTargets++] = sprite;
}
