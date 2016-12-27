#pragma once
#include <SFML\Graphics.hpp>
#include <iostream>
#include <cmath>
#include <string>
#include "Game.h"
#include "bullet.h"

using namespace std;
using namespace sf;
class Player
{
public:
	Player();
	~Player();
	/*float scale;*/

	float vSpeed;
	float hSpeed;
	float damage;

	bool hith;
	bool hitv;

	void checkCollision(Sprite wallSprites[],int nrOfWalls);

	void update(float deltaTime, RenderWindow &window);
	void draw(RenderWindow &window);
	void transform(float coordonataX,float coordonataY);
	void destroy();
	bool collision(Vector2i position);
	void lookAt(Vector2i target);
	void setScale(float x, float y);
	void tankRotation(float x,float y, RenderWindow &window);


	Vector2i direction;
	Sprite barrelSprite;
	Sprite tankSprite;
	Vector2i offset;
private:
	Texture tankTexture;
	Texture barrelTexture;
	
	float PI;
	/*bool setScale;*/
};

