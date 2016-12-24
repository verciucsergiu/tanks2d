#include "Game.h"

Game::Game()
{
	RenderWindow window(VideoMode(800, 574), "Tanks 2D", Style::Titlebar | Style::Close);
	cout << "window is open!\n";
	View followPlayer;
	followPlayer.setCenter(0, 0);
	followPlayer.setSize(800, 574);
	followPlayer.zoom(0.5);
	Player player;
	Clock clock;
	player.speed = 150;
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
				cout << "window is closed!\n";
			}
		}
		Time time = clock.getElapsedTime();
		player.update(time.asSeconds(), window);
		clock.restart().asSeconds();
		
		//cout <<"FPS are capped at 60: "<< (int)(1 / time.asSeconds()) << '\n';
		Color clearColor(150, 150, 150, 255);
		window.clear(clearColor);
		player.checkCollision(tileMap.wallCollision, tileMap.indexWallTileMap);
		tileMap.draw(window);
		player.draw(window);
		/*Vector2i mPosition = Mouse::getPosition();
		Vector2f followPos;
		followPos.x = mPosition.x-100;
		followPos.y = mPosition.y-100;*/
		Vector2f tankpos = player.tankSprite.getPosition();
		float currentDistanceY = Mouse::getPosition(window).y - player.offset.y;
		float currentDistanceX = Mouse::getPosition(window).x - player.offset.x;
		tankpos.x += (Mouse::getPosition(window).x / 4)*signbit(currentDistanceX);
		tankpos.y += (Mouse::getPosition(window).y / 4)*signbit(currentDistanceY);
		followPlayer.setCenter(player.tankSprite.getPosition());
		window.setView(followPlayer);
		
		//window.setView(window.getDefaultView());
		window.display();
	}
}


Game::~Game()
{
}