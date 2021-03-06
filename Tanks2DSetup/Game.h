#pragma once
#include "SFML\Graphics.hpp"
#include "Level.h"
#include "TextButton.h"
#include "hud.h"
#include <fstream>

using namespace std;
using namespace sf;

enum menuType {
	mainMenu, levelMenu, actualGame
};

struct GameLevelsObj
{
	Level level[15];
	int nrLevels;
};
struct GameLevels
{
	TextButton level[25];
	int nrLlevels;
};

class Game
{
public:
	Game();
	~Game();
private:
	void CreateCamera(float zoom);
	void displayFps();
	View followPlayer;
	Clock clock;
	float deltaTime;
	RenderWindow window;
	
	menuType currentMenu;
	
	TextButton quit;
	TextButton play;
	TextButton back;

	string levelsStrings[15];

	void createMainMenu();
	void createLevelsMenu();
	void createLoadingScreen();

	TextButton loadingText;

	void resetLevelsMenu();
	GameLevels levelsMenu;

	Stats playerStats;
	void getPlayerStats();
	
	GameLevelsObj levels;
	void resetLevels();
	void createLevels();
	int currentLevelPlaying;
	int maxLevels;
	hud gameHud;

	void saveStats();
};

