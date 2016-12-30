#pragma once
#include "SFML\Graphics.hpp"
#include <iostream>
#include <string>
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
	void tankRotation(int x,int y);

	void setBoxColliderOffset(float x,float y);
	void setScale(float x, float y);
	void setSpeed(float speed);
	void setRotationSpeed(float value);
private:
	Vector2i boxColliderOffset;
	Texture tankTexture;
	Texture barrelTexture;
	void defaultBoxColliderOffset();
	float PI = 3.14159265f;
	float vSpeed;
	float hSpeed;
	float rotationSpeed;
	float currentRotation;
};

