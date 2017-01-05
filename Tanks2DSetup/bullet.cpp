#include "bullet.h"



bullet::bullet()
{

}
bullet::~bullet()
{
}

void bullet::Update(float deltaTime, RenderWindow &window)
{
	shoot(deltaTime);
	draw(window);

}
void bullet::draw(RenderWindow &window)
{
	window.draw(bulletSprite);
}
void bullet::shoot(float deltaTime)
{
	float moveX = movement.x * speed * deltaTime;
	float moveY = movement.y * speed * deltaTime;
	bulletSprite.move(moveX,moveY);
}

void bullet::setTarget(int x, int y)
{
	target.x = x;
	target.y = y;
	calculateT();
}
void bullet::setSpeed(float value)
{
	speed = value;
}
void bullet::calculateT()
{
	float x = target.x - startPos.x;
	float y = target.y - startPos.y;
	float normalize = sqrt(x*x + y*y);
	x = x / normalize;
	y = y / normalize;
	movement.x = x;
	movement.y = y;
	cout << x << " " << y<<'\n';
}

void bullet::setStartPosition(int x, int y)
{
	bulletSprite.setPosition(x, y);
	startPos.x = x;
	startPos.y = y;
}

void bullet::create()
{
	if (!bulletTexture.loadFromFile("sprites/bullet.png"))
	{
			cout << "Error loading the bullet\n";
	}
	bulletSprite.setTexture(bulletTexture);
	float x = bulletSprite.getGlobalBounds().height / 2;
	float y = bulletSprite.getGlobalBounds().width / 2;
	bulletSprite.setOrigin(x, y);
}
