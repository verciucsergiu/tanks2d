#include "bullet.h"
#include "Player.h"


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
void bullet::setBulletRotation(Vector2i target, RenderWindow &window)
{
	Vector2i currentPos = window.mapCoordsToPixel(bulletSprite.getPosition(), window.getView());

	const float PI = 3.14159265;
	float dx = currentPos.x - target.x;
	float dy = currentPos.y - target.y;

	//am adaugat asta pt ca turela nu urmareste mouse-ul cum trebuie altfel
	dx = -dx;
	dy = -dy;

	float turretRotation = (atan2(dy, dx)) * 180 / PI;
	//am scos "float rotation" de aici si l-am adaugat in private
	//am nevoie de el in bullet.cpp
	turretRotation += 90.0f;
	bulletSprite.setRotation(turretRotation);
}
void bullet::setColliders(Collider2D * first, Collider2D * last)
{
	collFirst = first;
	collLast = last;
}
bool bullet::checkCollision()
{
	for (Collider2D * current = collFirst; current != nullptr; current = current->next)
	{
		FloatRect rect(bulletSprite.getPosition().x, bulletSprite.getPosition().y, 20, 20);
		if (current->target.getGlobalBounds().intersects(rect))
		{
			collisionType = 0;
			if (current->role == 1)
			{
				collisionType = 1;
			}
			if (current->role == 2)
			{
				collisionType = 2;
				colTarget = rect;
			}
			return true;
		}
	}
	return false;
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
