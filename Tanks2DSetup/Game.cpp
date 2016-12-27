#include "Game.h"

Game::Game()
{
	RenderWindow window(VideoMode(800, 574), "Tanks 2D", Style::Titlebar | Style::Close);
	View followPlayer;
	followPlayer.setCenter(0, 0);
	followPlayer.setSize(800, 574);
	followPlayer.zoom(0.65);
	Player player;
	Clock clock;
	player.vSpeed = 150;
	player.hSpeed = 150;
	window.setFramerateLimit(59);
	player.setScale(1.3, 1.3);
	player.transform(400, 300);

	for (int i = 0; i < 21; i++)
	{
		tileMap.addTile(i, 0, GameMap::tileType::wall);
		tileMap.addTile(0, i, GameMap::tileType::wall);
		tileMap.addTile(21, i, GameMap::tileType::wall);
		tileMap.addTile(i, 21, GameMap::tileType::wall);
	}
	tileMap.addTile(21, 21, GameMap::tileType::wall);

	for (int i = 0; i < tileMap.indexWallTileMap; i++)
	{
		tileMap.wallCollision[i].setTexture(tileMap.wallTexture);
		tileMap.wallCollision[i].setPosition(tileMap.wallAdress[i].x, tileMap.wallAdress[i].y);
	}

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
		player.checkCollision(tileMap.wallCollision, tileMap.indexWallTileMap);

		player.update(time.asSeconds(), window);
		clock.restart().asSeconds();
		
		Color clearColor(150, 150, 150, 255);
		window.clear(clearColor);
		
		tileMap.draw(window);
		player.draw(window);
		Vector2f tankpos = player.tankSprite.getPosition();
		
		Font font;
		font.loadFromFile("sansation.ttf");
		String dirX = "Direction X : " + to_string(player.direction.x);
		
		Text textX(dirX, font);
		textX.setCharacterSize(15);
		textX.setPosition(tankpos.x - 220, tankpos.y -50);
		window.draw(textX);

		String dirY = "Dirextion Y : " + to_string(player.direction.y);
		Text textY(dirY, font);
		textY.setCharacterSize(15);
		textY.setPosition(tankpos.x - 220, tankpos.y - 20);
		window.draw(textY);

		String fps = "FPS: " + to_string((int)(1 / time.asSeconds()));
		Text fpsT(fps, font);
		fpsT.setCharacterSize(15);
		fpsT.setPosition(tankpos.x - 220, tankpos.y+10);
		window.draw(fpsT);

		String hitv = "Collision vert: " + to_string(player.hitv);
		Text hitVText(hitv, font);
		hitVText.setCharacterSize(15);
		hitVText.setPosition(tankpos.x - 220, tankpos.y + 30);
		window.draw(hitVText);

		String hith = "Collision hozi: " + to_string(player.hith);
		Text hitHText(hith, font);
		hitHText.setCharacterSize(15);
		hitHText.setPosition(tankpos.x - 220, tankpos.y + 50);
		window.draw(hitHText);

		followPlayer.setCenter(tankpos);
		window.setView(followPlayer);
		
		window.display();
	}
}


Game::~Game()
{
	
}