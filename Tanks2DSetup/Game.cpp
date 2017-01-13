#include "Game.h"

Game::Game()
{
	window.create(VideoMode(800, 576), "TANKS 2D", Style::Titlebar | Style::Close);
	getPlayerStats();
	CreateCamera(1);
	resetLevelsMenu();

	createLevelsMenu();
	createMainMenu();
	createLoadingScreen();
	

	resetLevels();
	createLevels();

	sf::Texture sandLevelTexture;
	sf::Sprite sandSprite;
	sf::Texture introGame;
	sf::Sprite introSrite;
	if(!sandLevelTexture.loadFromFile("sprites/sand.png"))
	{
		cout << "Error loading sand!\n";
	}
	if (!introGame.loadFromFile("sprites/intro.png"))
	{
		cout << "Error loading intro!\n";
	}
	sf::Texture levelText;
	if (!levelText.loadFromFile("sprites/levelmenu.png"))
	{
		cout << "Error loading levelmenu!\n";
	}
	
	sf::Sprite levelSprite;
	introSrite.setTexture(introGame);
	introSrite.setPosition(-400, -288);
	levelSprite.setTexture(levelText);
	levelSprite.setPosition(-400, -288);
	
	sandLevelTexture.setRepeated(true);

	sandSprite.setTexture(sandLevelTexture);
	sandSprite.setTextureRect({0,0,5000,5000});

	currentMenu = menuType::mainMenu;

	bool levelFailedCreated = false;
	bool pause = false;
	bool contCreated = false;
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
		
		Vector2f mousePos = window.mapPixelToCoords(Mouse::getPosition(window));
		switch (currentMenu)
		{
		case mainMenu:
		{
			window.draw(introSrite);
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
			window.draw(levelSprite);
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
						levels.level[i].player.setAlive(true);
						getPlayerStats();
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
			
			if (!pause)
			{
				levels.level[currentLevelPlaying].setPause(false);
				if (!levels.level[currentLevelPlaying].player.isAlive())
				{
					levels.level[currentLevelPlaying].Update(0, window);
					TextButton youFailed;
					TextButton replay;
					replay.create("Back to menu", levels.level[currentLevelPlaying].getCameraPos().x, levels.level[currentLevelPlaying].getCameraPos().y + 155, Color::Blue, sizeType::mediu);
					youFailed.create("You failed where everyone else prevailed!\nAdjust your gameplay!!!", levels.level[currentLevelPlaying].getCameraPos().x, levels.level[currentLevelPlaying].getCameraPos().y, Color::Red, sizeType::large);
					youFailed.Draw(window);
					replay.Draw(window);
					replay.checkHover(mousePos.x, mousePos.y, window);
					if (Mouse::isButtonPressed(Mouse::Button::Left) && replay.checkClick(mousePos.x,mousePos.y))
					{
						followPlayer.setCenter(0, 0);
						window.setView(followPlayer);
						currentMenu = menuType::levelMenu;
						levels.level[currentLevelPlaying].setPlay();
						getPlayerStats();
						levels.level[currentLevelPlaying].setPlayerStats(playerStats);
					}
				}
				else
				{
					levels.level[currentLevelPlaying].Update(deltaTime, window);
					if (levels.level[currentLevelPlaying].gameEnd())
					{
						followPlayer.setCenter(0, 0);
						window.setView(followPlayer);
						currentMenu = menuType::levelMenu;
						if (currentLevelPlaying + 1 <= maxLevels)
						{
							levelsMenu.level[currentLevelPlaying + 1].setActive(true);
							playerStats.currentLevel++;
							saveStats();
						}
					}
				}
			}

			if (Keyboard::isKeyPressed(Keyboard::Key::Escape) && !pause)
			{
				pause = true;
			
				
			}
			if (pause)
			{
				TextButton continuePlay;
				continuePlay.Draw(window);
				continuePlay.create("Play", levels.level[currentLevelPlaying].getCameraPos().x, levels.level[currentLevelPlaying].getCameraPos().y, Color::Red, sizeType::mediu);
				TextButton backMenu;
				backMenu.Draw(window);
				backMenu.create("Back to menu", levels.level[currentLevelPlaying].getCameraPos().x, levels.level[currentLevelPlaying].getCameraPos().y + 50, Color::Red, sizeType::mediu);
				levels.level[currentLevelPlaying].setPause(false);
				levels.level[currentLevelPlaying].Update(0, window);
				continuePlay.Draw(window);
				continuePlay.checkHover(mousePos.x, mousePos.y, window);
				if (continuePlay.checkClick(mousePos.x,mousePos.y) && Mouse::isButtonPressed(Mouse::Left))
				{
					pause = false;
					contCreated = false;
				}
				backMenu.Draw(window);
				backMenu.checkHover(mousePos.x, mousePos.y, window);
				if (backMenu.checkClick(mousePos.x, mousePos.y) && Mouse::isButtonPressed(Mouse::Left))
				{
					followPlayer.setCenter(0, 0);
					window.setView(followPlayer);
					currentMenu = menuType::levelMenu;
					pause = false;
					contCreated = false;
				}
			}
			gameHud.health = levels.level[currentLevelPlaying].player.health;
			gameHud.draw(window);
		}
			break;
		}
		//displayFps();
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
			if (level > playerStats.currentLevel)
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

	levelsStrings[0] = "level1.txt";
	levelsStrings[1] = "level2.txt";
	levelsStrings[2] = "level3.txt";
	levels.level[0].GenerateMap(levelsStrings[0]);
	levels.level[1].GenerateMap(levelsStrings[1]);
	levels.level[2].GenerateMap(levelsStrings[2]);
	maxLevels = 2;
}

void Game::saveStats()
{
	ofstream out("playerStats.txt");
	out << playerStats.health<<" "<< playerStats.damage<<" "<< playerStats.currentLevel<< "\n" << playerStats.speed<<" "<< playerStats.bulletSpeed;
	out.close();
}

void Game::createMainMenu()
{
	quit.create("Quit", window.getView().getCenter().x, window.getView().getCenter().y + 80, Color::Red, sizeType::mediu);
	play.create("Play", window.getView().getCenter().x, window.getView().getCenter().y, Color::Blue, sizeType::mediu);
}
