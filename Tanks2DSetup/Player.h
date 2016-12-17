#pragma once
#include <SFML\Graphics.hpp>
#include <iostream>
#include <cmath>
#include "bullet.h"

using namespace std;
using namespace sf;
class Player
{
public:
	Player();
	~Player();
	/*float scale;*/

	float speed;
	float damage;


	void update(float deltaTime, RenderWindow &window);
	void draw(RenderWindow &window);
	void transform(float coordonataX,float coordonataY);
	void destroy();
	bool collision(Vector2i position);
	void lookAt(Vector2i target);
	void setScale(float x, float y);
	void tankRotation(float x,float y, RenderWindow &window);
	Sprite barrelSprite;
	Sprite tankSprite;
private:
	Texture tankTexture;
	Texture barrelTexture;
	Vector2i offset;
	float PI;
	/*bool setScale;*/
};

