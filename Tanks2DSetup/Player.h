#pragma once
#include "SFML\Graphics.hpp"
#include <iostream>
#include <string>

using namespace std;
using namespace sf;

struct Collider
{
	Sprite target;
	Collider * next;
};

class Player
{
public:
	Player();
	~Player();
	/*Stats*/
	int damage;
	int health;
	/*No more stats*/
	Sprite barrelSprite;
	Sprite tankSprite;
	

	void startPosition(float x, float y);
	void update(float deltaTime, RenderWindow &window);

	Collider * collFirst;
	Collider * collLast;
	void addCollider(Sprite sprite);
	void resetCollider();

	bool Player::collisionHorizontal(float dir);
	bool Player::collisionVertical(float dir);

	void draw(RenderWindow &window);
	void destroy();

	void lookAt(Vector2i target,RenderWindow &window);
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
	float fixedDeltaTime;
	float rotationSpeed;
	float currentRotation;

	bool testing;
};

