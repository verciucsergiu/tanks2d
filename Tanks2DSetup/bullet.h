#pragma once
#include <SFML\Graphics.hpp>
#include <iostream>

using namespace std;
using namespace sf;

class bullet
{
public:
	bullet();
	~bullet();
	Sprite bulletSprite;
	void setPosition(int x, int y);
	void translate(Vector2i target);
	void Update(float deltaTime, RenderWindow &window);
	void shoot(float dirX, float dirY);
private:
	void draw(RenderWindow &window);
	Texture bulletTexture;
	bool hit;
};

