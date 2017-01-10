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

void bullet::addCollider(Sprite sprite,int roleValue)
{
	if (collFirst != nullptr && collLast != nullptr)
	{
		Collider2D * add = new Collider2D;
		add->target = sprite;
		add->role = roleValue;
		add->next = nullptr;
		collLast->next = add;
		collLast = add;
	}
	else
	{
		Collider2D * add = new Collider2D;
		add->target = sprite;
		add->role = roleValue;
		add->next = nullptr;
		collFirst = add;
		collLast = collFirst;
	}
}
void bullet::resetCollider()
{
	collFirst = nullptr;
	collLast = nullptr;
}
bool bullet::checkCollision()
{
	for (Collider2D * current = collFirst; current != nullptr; current = current->next)
	{
		FloatRect rect(bulletSprite.getPosition().x, bulletSprite.getPosition().y, 4, 4);
		if (current->target.getGlobalBounds().intersects(rect))
		{
			collisionType = 0;
			if (current->role == 1)
			{
				
				collisionType = 1;
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
	resetCollider();
	if (!bulletTexture.loadFromFile("sprites/bullet.png"))
	{
			cout << "Error loading the bullet\n";
	}
	bulletSprite.setTexture(bulletTexture);
	float x = bulletSprite.getGlobalBounds().height / 2;
	float y = bulletSprite.getGlobalBounds().width / 2;
	bulletSprite.setOrigin(x, y);
}
