#pragma once
#include <SFML\Graphics.hpp>
#include <iostream>
#include <math.h>

using namespace std;
using namespace sf;

struct Collider2D
{
	Sprite target;
	int role;
	Collider2D * next;
};

class bullet
{
public:
	bullet();
	~bullet();
	Sprite bulletSprite;
	void setStartPosition(int x, int y);
	void setBulletRotation(Vector2i mousePosition, sf::RenderWindow &window);
	void create();
	void Update(float deltaTime, RenderWindow &window);
	void shoot(float deltaTime);
	void setTarget(int x, int y);
	void setSpeed(float value);

	Collider2D *collFirst;
	Collider2D *collLast;
	void setColliders(Collider2D *first, Collider2D *last);
	bool checkCollision();
	int collisionType;
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

