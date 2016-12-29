#include "Game.h"

Game::Game()
{
	RenderWindow window(VideoMode(800, 574), "Tanks 2D", Style::Titlebar | Style::Close);
	window.setFramerateLimit(59);

	Clock clock;

	View followPlayer;
	followPlayer.setCenter(0, 0);
	followPlayer.setSize(800, 574);
	followPlayer.zoom(0.65);

	Player player;
	player.setSpeed(150);
	player.setScale(1.3, 1.3);
	player.startPosition(-100, -20);
	player.setBoxColliderOffset(-2, -3);

	GameMap tileMap;
	
	int walls = 5;

	for (int i = 0; i < walls; i++)
	{
		tileMap.addTile(i, 0, GameMap::tileType::wall);
		tileMap.addTile(0, i, GameMap::tileType::wall);
		tileMap.addTile(walls, i, GameMap::tileType::wall);
		tileMap.addTile(i, walls, GameMap::tileType::wall);
	}
	tileMap.addTile(walls, walls, GameMap::tileType::wall);

	
	//collision
	for (int i = 0; i < tileMap.indexWallTileMap; i++)
	{
		player.collider.target[i].setTexture(tileMap.wallTexture);
		player.collider.target[i].setPosition(tileMap.wallAdress[i].x, tileMap.wallAdress[i].y);
		player.collider.numberOfTargets = tileMap.indexWallTileMap;
	}

	//enemy to add to player.collider.target[i]
	//metoda ineficienta de a verifica fiecare obstacol in parte dar mai putin cod de scris

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
		
		//DrawThings
		tileMap.draw(window);
		player.draw(window);


		//DEBUGING
		Vector2f tankpos = player.tankSprite.getPosition();
	
		Font font;
		font.loadFromFile("sansation.ttf");

		String fps = "FPS: " + to_string((int)(1 / time.asSeconds()));
		Text fpsT(fps, font);
		fpsT.setCharacterSize(15);
		fpsT.setPosition(tankpos.x - 220, tankpos.y+10);
		window.draw(fpsT);

		//CAMERA MOVEMENT
		followPlayer.setCenter(tankpos);
		window.setView(followPlayer);
	
		window.display();
	}
}


Game::~Game()
{
	
}