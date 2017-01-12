#include "Game.h"

Game::Game()
{
	window.create(VideoMode(800, 576), "TANKS 2D", Style::Titlebar | Style::Close);

	CreateCamera(1);
	resetLevelsMenu();

	createLevelsMenu();
	createMainMenu();
	createLoadingScreen();
	
	getPlayerStats();
	resetLevels();
	createLevels();

	sf::Texture sandLevelTexture;
	sf::Sprite sandSprite;

	if(!sandLevelTexture.loadFromFile("sprites/sand.png"))
	{
		cout << "Error loading tile_ground!\n";
	}


	sandLevelTexture.setRepeated(true);

	sandSprite.setTexture(sandLevelTexture);
	sandSprite.setTextureRect({0,0,5000,5000});

	currentMenu = menuType::mainMenu;
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
		clock.restart().asSeconds();
		
		window.clear();
		
		if (Keyboard::isKeyPressed(Keyboard::Key::Escape))
		{
			currentMenu = menuType::levelMenu;
		}

		Vector2f mousePos = window.mapPixelToCoords(Mouse::getPosition(window));
		switch (currentMenu)
		{
		case mainMenu:
		{
			quit.Draw(window);
			play.Draw(window);
			quit.checkHover(mousePos.x, mousePos.y, window);
			play.checkHover(mousePos.x, mousePos.y, window);
			if (Mouse::isButtonPressed(Mouse::Button::Left))
			{
				if (play.checkClick(mousePos.x,mousePos.y) && play.isActive())
				{
					currentMenu = menuType::levelMenu;
				}
				if (quit.checkClick(mousePos.x, mousePos.y) && quit.isActive())
				{
					window.close();
				}

			}
			
		}
			break;
		case levelMenu:
		{			
			back.Draw(window);
			back.checkHover(mousePos.x, mousePos.y, window);
			for (int i = 0; i < levelsMenu.nrLlevels; i++)
			{
				levelsMenu.level[i].Draw(window);
				levelsMenu.level[i].checkHover(mousePos.x, mousePos.y, window);
			}
			if (Mouse::isButtonPressed(Mouse::Button::Left))
			{
				
				if (back.checkClick(mousePos.x, mousePos.y) && back.isActive())
				{
					currentMenu = menuType::mainMenu;
				}
				for (int i = 0; i < levelsMenu.nrLlevels; i++)
				{
					if (levelsMenu.level[i].checkClick(mousePos.x, mousePos.y) && levelsMenu.level[i].isActive())
					{
						currentLevelPlaying = i;
						currentMenu = menuType::actualGame;
						levels.level[i].Create();
						levels.level[i].setPlayerStats(playerStats);
						levels.level[i].setPlay();
					}
				}
			}
		}
			break;
		case actualGame:
		{
			window.draw(sandSprite);
			levels.level[currentLevelPlaying].Update(deltaTime, window);
			if (levels.level[currentLevelPlaying].gameEnd())
			{
				followPlayer.setCenter(0, 0);
				window.setView(followPlayer);
				currentMenu = menuType::levelMenu;
				if (currentLevelPlaying + 1 <= maxLevels)
				{
					levelsMenu.level[currentLevelPlaying + 1].setActive(true);
				}
			}
				
		}
			break;
		}
		
		displayFps();
		window.display();
	}
}
Game::~Game()
{
	
}

void Game::CreateCamera(float zoom)
{
	followPlayer.setCenter(0, 0);
	followPlayer.setSize(window.getSize().x, window.getSize().y);
	followPlayer.zoom(zoom);
	window.setView(followPlayer);
}

void Game::displayFps()
{
	Font font;
	font.loadFromFile("sansation.ttf");
	String fps = "FPS: " + to_string((int)(1 / deltaTime));
	Text fpsT(fps, font);
	fpsT.setCharacterSize(15);
	fpsT.setPosition(window.getView().getCenter().x - window.getView().getSize().x / 2, window.getView().getCenter().y - window.getView().getSize().y / 2);
	window.draw(fpsT);
	if (currentMenu == menuType::actualGame)
	{
		String str = "X: " + to_string((int)levels.level[currentLevelPlaying].player.tankSprite.getPosition().x) + "\nY: " + to_string((int)levels.level[currentLevelPlaying].player.tankSprite.getPosition().y);
		Text strText(str, font);
		strText.setCharacterSize(15);
		strText.setPosition(window.getView().getCenter().x - window.getView().getSize().x / 2, window.getView().getCenter().y - window.getView().getSize().y / 2 + 20);
		window.draw(strText);
	}
}

void Game::createLevelsMenu()
{
	back.create("Back", window.getView().getCenter().x - window.getView().getSize().x / 2 + 150, window.getView().getCenter().y - window.getView().getSize().y / 2 + 55, Color::Yellow, sizeType::mediu);
	float startX = window.getView().getCenter().x - window.getView().getSize().x / 2 + 180;
	float startY = window.getView().getCenter().y - window.getView().getSize().y / 2 + 180;
	float spacing = 100;
	int level = 0;
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			levelsMenu.level[level++].create(to_string(level), startX + j*spacing, startY + i*spacing, Color::Blue, sizeType::small);
			if (level > 1)
			{
				levelsMenu.level[level - 1].setActive(false);
			}
		}
	}
	levelsMenu.nrLlevels = level;
}
void Game::createLoadingScreen()
{
	loadingText.create("Loading level...", window.getView().getCenter().x, window.getView().getCenter().y);
}
void Game::resetLevelsMenu()
{
	levelsMenu.nrLlevels = 0;
}


void Game::getPlayerStats()
{
	ifstream fin("playerStats.txt");
	fin >> playerStats.health;
	fin >> playerStats.damage;
	fin >> playerStats.currentLevel;
	fin >> playerStats.speed;
	fin >> playerStats.bulletSpeed;
	fin.close();
}

void Game::resetLevels()
{
	levels.nrLevels = 0;
}

void Game::createLevels()
{

	levels.level[0].Create();
	levels.level[0].GenerateMap("level1.txt");
	levels.level[1].Create();
	levels.level[1].GenerateMap("level2.txt");
	levels.level[1].setPlayerStats(playerStats);
	maxLevels = 1;
}

void Game::createMainMenu()
{
	quit.create("Quit", window.getView().getCenter().x, window.getView().getCenter().y + 80, Color::Red, sizeType::mediu);
	play.create("Play", window.getView().getCenter().x, window.getView().getCenter().y, Color::Blue, sizeType::mediu);
}
