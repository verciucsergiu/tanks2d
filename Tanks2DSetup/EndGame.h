#pragma once
#include <SFML\Graphics.hpp>
#include <iostream>

using namespace sf;
using namespace std;
class EndGame
{
public:
	EndGame();
	~EndGame();
	Texture finishTexture;
	Sprite finishSprite;
	int health;
	void draw(RenderWindow &window);
	void setPosition(int gridX, int gridY, int x, int y);
	void takeDamage(int value);

	bool isAlive();
private:
	bool alive;
};

