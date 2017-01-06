#pragma once
#include "Level.h"
#include "TextButton.h"


using namespace std;
using namespace sf;

enum menuType {
	mainMenu, levelMenu, actualGame
};
struct GameLevels
{
	TextButton level[100];
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

	void createMainMenu();
	void createLevelsMenu();
	void createLoadingScreen();

	TextButton loadingText;

	void resetLevels();
	GameLevels levels;

};

