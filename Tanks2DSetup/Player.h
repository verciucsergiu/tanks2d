#pragma once
#include <SFML\Graphics.hpp>
#include <iostream>
#include <cmath>
#include <string>
#include "Game.h"
#include "bullet.h"

using namespace std;
using namespace sf;

#define MAX_TARGETS 1000

struct Collider
{
	Sprite target[MAX_TARGETS];
	int numberOfTargets;
};

class Player
{
public:
	Player();
	~Player();

	Sprite barrelSprite;
	Sprite tankSprite;

	float damage;

	void startPosition(float x, float y);
	void update(float deltaTime, RenderWindow &window);

	Collider collider;
	bool Player::collisionHorizontal(float dir);
	bool Player::collisionVertical(float dir);


	void draw(RenderWindow &window);
	void destroy();

	void lookAt(Vector2i target, Vector2i halfSizeWindow);
	void tankRotation(float x,float y, RenderWindow &window);

	void setBoxColliderOffset(int x,int y);
	void setScale(float x, float y);
	void setSpeed(float speed);
	
	

	//variabile care vor fi trecute private cand "DEBUG ends"
	Vector2i collisionDirection;

private:
	Vector2i boxColliderOffset;
	Vector2i initialPosition;
	Texture tankTexture;
	Texture barrelTexture;
	void resetCollision();
	void defaultBoxColliderOffset();
	float PI = 3.14159265;
	float vSpeed;
	float hSpeed;
	/*bool setScale;*/
};

