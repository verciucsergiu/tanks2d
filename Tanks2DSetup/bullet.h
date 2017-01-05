#pragma once
#include <SFML\Graphics.hpp>
#include <iostream>
#include <math.h>

using namespace std;
using namespace sf;

class bullet
{
public:
	bullet();
	~bullet();
	Sprite bulletSprite;
	void setStartPosition(int x, int y);
	void create();
	void Update(float deltaTime, RenderWindow &window);
	void shoot(float deltaTime);
	void setTarget(int x, int y);
	void setSpeed(float value);
private:
	void draw(RenderWindow &window);
	Texture bulletTexture;
	bool hit;
	int index;
	Vector2i target;
	Vector2i startPos;
	Vector2f movement;
	void calculateT();
	float speed;
};

