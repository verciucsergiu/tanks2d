#pragma once
#include "SFML\Graphics.hpp"
#include <iostream>
#include <string>
using namespace sf;
using namespace std;

class Tower
{
public:
	Tower();
	~Tower();
	Sprite tunSprite;
	Sprite towerSprite;
	Texture tunTexture;
	Texture towerTexture;
	int health;
	void setPosition(int gridX, int gridY, int x, int y);
	void draw(RenderWindow &window);

	void takeDamage(int value);
	bool isAlive;
private:
	Sprite bulletTexture;

};

