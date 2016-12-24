#include "bullet.h"



bullet::bullet()
{
	if (!bulletTexture.loadFromFile("sprites/bullet.png"))
	{
	//	cout << "Error loading the bullet\n";
	}
	//cout << "Sprite loaded!\n";
	bulletSprite.setTexture(bulletTexture);
	bulletSprite.setScale(10, 10);
}
bullet::~bullet()
{
}

void bullet::Update(float deltaTime, RenderWindow &window)
{
	draw(window);
}
void bullet::draw(RenderWindow &window)
{
	//cout << "Sprite draw!\n";
	window.draw(bulletSprite);
}
void bullet::shoot(float dirX, float dirY)
{
	float distThisFrame;
}
void bullet::translate(Vector2i target)
{
	
}

void bullet::setPosition(int x, int y)
{
	//cout << "Bullet position :(" << x << "," << y << ")\n";
	bulletSprite.setPosition(x, y);
}
