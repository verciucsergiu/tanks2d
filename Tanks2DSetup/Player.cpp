#include "Player.h"

Player::Player()
{
	
}

Player::~Player()
{
	
}

void Player::create()
{
	if (!tankTexture.loadFromFile("sprites/tank_base.png"))
	{
		cout << "Error loading the tank_base!\n";
	}
	if (!barrelTexture.loadFromFile("sprites/tank_turel.png"))
	{
		cout << "Error loading the tank_turel!\n";
	}
	tankSprite.setTexture(tankTexture);
	barrelSprite.setTexture(barrelTexture);

	float x = barrelSprite.getOrigin().x + 16;
	float y = barrelSprite.getOrigin().y + 16;
	tankSprite.setOrigin(x, y); // setare pivot centru scop = rotire corecta
	x += 6;
	barrelSprite.setOrigin(x, y); // setare pivot centru x+3 scop = rotire corecta a turelei	
	defaultBoxColliderOffset();
}

void Player::startPosition(float x, float y)
{
	Vector2f position(x, y);
	tankSprite.setPosition(position);
	barrelSprite.setPosition(position);
}

void Player::update(float deltaTime,RenderWindow &window)
{
	Vector2i mousePosition = Mouse::getPosition(window);
	Vector2i halfSizeWindow(window.getSize().x / 2, window.getSize().y / 2);
	lookAt(mousePosition,halfSizeWindow);

	Vector2i movement(0,0);
	if (Keyboard::isKeyPressed(Keyboard::W) && !collisionVertical(-1))
	{
		movement.y -= 1;
	}
	if (Keyboard::isKeyPressed(Keyboard::A) && !collisionHorizontal(-1))
	{
		movement.x -= 1;
	}
	if (Keyboard::isKeyPressed(Keyboard::S) && !collisionVertical(1))
	{
		movement.y += 1;
	}
	if (Keyboard::isKeyPressed(Keyboard::D) && !collisionHorizontal(1)) 
	{
		movement.x += 1;
	}

	tankSprite.move(movement.x * deltaTime * vSpeed, movement.y * deltaTime * hSpeed);
	barrelSprite.move(movement.x * deltaTime * vSpeed, movement.y * deltaTime * hSpeed);

	/*if (Mouse::isButtonPressed(Mouse::Button::Left))
	{
		//cout << "Fired : (" << barrelSprite.getPosition().x << "," << barrelSprite.getPosition().y << ")\n";
		bullet bulletFired;
		bulletFired.setPosition(barrelSprite.getPosition().x,barrelSprite.getPosition().y);
		bulletFired.Update(deltaTime, window);
	}*/
	
}
bool Player::collisionVertical(float dir)
{
	for (int i = 0; i < collider.numberOfTargets; i++)
	{
		float y = tankSprite.getPosition().y + 17 * dir + boxColliderOffset.y * dir;
		if (collider.target[i].getGlobalBounds().contains(tankSprite.getPosition().x - dir * 16, y))
		{
			return true;
		}
		if (collider.target[i].getGlobalBounds().contains(tankSprite.getPosition().x, y))
		{
			return true;
		}
		if (collider.target[i].getGlobalBounds().contains(tankSprite.getPosition().x + 16 * dir, y))
		{
			return true;
		}
	}
	return false;
}
bool Player::collisionHorizontal(float dir)
{
	for (int i = 0; i < collider.numberOfTargets; i++)
	{
		float x = tankSprite.getPosition().x + 17 * dir + boxColliderOffset.x * dir;
		if (collider.target[i].getGlobalBounds().contains(x, tankSprite.getPosition().y - dir * 16))
		{
			return true;
		}
		if (collider.target[i].getGlobalBounds().contains(x, tankSprite.getPosition().y))
		{
			return true;
		}
		if (collider.target[i].getGlobalBounds().contains(x, tankSprite.getPosition().y + dir * 16))
		{
			return true;
		}
	}
	return false;
}
void Player::draw(RenderWindow &window)
{	
	window.draw(tankSprite);
	window.draw(barrelSprite);
}
void Player::destroy()
{
	Color color(0.f, 0.f, 0.f, 0.f);
	tankSprite.setColor(color);
}
void Player::lookAt(Vector2i target,Vector2i halfSizeWindow)
{
	Vector2f curentPos = barrelSprite.getPosition();

	const float PI = 3.14159265;
	float dx = halfSizeWindow.x - target.x;
	float dy = halfSizeWindow.y - target.y;

	float rotation = (atan2(dy, dx)) * 180 / PI;

	barrelSprite.setRotation(rotation);
}
void Player::setBoxColliderOffset(float x, float y)
{
	boxColliderOffset.x = x;
	boxColliderOffset.y = y;
}
void Player::setScale(float x, float y)
{
	barrelSprite.setScale(x, y);
	tankSprite.setScale(x, y);
}
void Player::setSpeed(float value)
{
	vSpeed = value;
	hSpeed = value;
}
void Player::defaultBoxColliderOffset()
{
	boxColliderOffset.x = 0;
	boxColliderOffset.y = 0;
}
