#pragma once
#include "SFML\Graphics.hpp"
#include <iostream>
#include <string>
using namespace sf;
using namespace std;

enum sizeType
{
	small,mediu,large 
};

class TextButton
{
public:
	TextButton();
	~TextButton();
	void Draw(RenderWindow &window);
	void create(string text, int positionX, int positionY,Color color = Color::Black,sizeType value = sizeType::mediu);
	bool checkClick(int x, int y);
	void checkHover(int x, int y,RenderWindow &window);
	void setActive(bool value);
	bool isActive();

private:
	Texture buttonTexture;
	Sprite buttonSprite;
	Font font;
	Text textDisplay;
	bool aviable;
};

