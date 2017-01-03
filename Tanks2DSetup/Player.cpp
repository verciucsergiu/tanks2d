#include "Player.h"

Player::Player()
{
	currentRotation = 0;

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

Player::~Player()
{
	
}
void Player::startPosition(float x, float y)
{
	Vector2f position(x, y);
	tankSprite.setPosition(position);
	barrelSprite.setPosition(position);
}

void Player::update(float deltaTime,RenderWindow &window)
{
	fixedDeltaTime = deltaTime;
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
	tankRotation(movement.x, movement.y);
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
void Player::tankRotation(int dirX, int dirY)
{
	//wtf should i do :(
	if (currentRotation < 0)
	{
		currentRotation = 360 + currentRotation;
	}
	if (currentRotation >360)
	{
		currentRotation = currentRotation - 360;
	}
	if (dirX && dirY == 0)
	{
		if (dirX == -1)
		{
			if (currentRotation >= 180 + fixedDeltaTime * 100 || currentRotation <= 180 - fixedDeltaTime * 100)
			{
				if (currentRotation>180)
				{
					currentRotation -= rotationSpeed * fixedDeltaTime;
				}
				else
				{
					currentRotation += rotationSpeed * fixedDeltaTime;
				}
			}
		}
		else
		{
			if (currentRotation >= 0 + fixedDeltaTime * 100 || currentRotation <= 0 - fixedDeltaTime * 100)
			{
				if (currentRotation>180)
				{
					currentRotation += rotationSpeed * fixedDeltaTime;
				}
				else
				{
					currentRotation -= rotationSpeed * fixedDeltaTime;
				}
			}
		}
	}
	else if (dirX == 0 && dirY)
	{
		if (dirY == 1)
		{
			if (currentRotation >= 90 + fixedDeltaTime * 100 || currentRotation <= 90 - fixedDeltaTime * 100)
			{
				if (currentRotation <270 && currentRotation > 90)
				{
					currentRotation -= rotationSpeed * fixedDeltaTime;
				}
				else
				{
					currentRotation += rotationSpeed * fixedDeltaTime;
				}
			}
			
		}
		else
		{
			if (currentRotation >= 270 + fixedDeltaTime * 100 || currentRotation <= 270 - fixedDeltaTime * 100)
			{
				if (currentRotation < 270 && currentRotation > 90)
				{
					currentRotation += rotationSpeed * fixedDeltaTime;
				}
				else
				{
					if (currentRotation<=360||currentRotation==0)
					{
						currentRotation -= rotationSpeed * fixedDeltaTime;
					}
					else if (currentRotation < 90)
					{
						currentRotation -= rotationSpeed * fixedDeltaTime;
					}
				}
			}
		}
	}
	else if (dirX && dirY)
	{
		if (dirX == 1 && dirY == 1) // 45
		{
			if (currentRotation >= 45 + fixedDeltaTime * 100 || currentRotation <= 45 - fixedDeltaTime * 100)
			{
				if (currentRotation < 225 && currentRotation > 45)
				{
					currentRotation -= rotationSpeed * fixedDeltaTime;
				}
				else
				{
					currentRotation += rotationSpeed * fixedDeltaTime;
				}
			}
			
		}
		if (dirX == -1 && dirY == 1) // 135
		{
			if (currentRotation >= 135 + fixedDeltaTime * 100 || currentRotation <= 135 - fixedDeltaTime * 100)
			{
				if (currentRotation < 315 && currentRotation > 135)
				{
					currentRotation -= rotationSpeed * fixedDeltaTime;
				}
				else
				{
					currentRotation += rotationSpeed * fixedDeltaTime;
				}
			}
		}
		if (dirX == -1 && dirY == -1) //225
		{
			if (currentRotation >= 225 + fixedDeltaTime * 100 || currentRotation <= 225 - fixedDeltaTime * 100)
			{
				if (currentRotation < 225 && currentRotation > 45)
				{
					currentRotation += rotationSpeed * fixedDeltaTime;
				}
				else
				{
					currentRotation -= rotationSpeed * fixedDeltaTime;
				}
			}
		}
		if (dirX == 1 && dirY == -1) // 315
		{
			if (currentRotation >= 315 + fixedDeltaTime * 100 || currentRotation <= 315 - fixedDeltaTime * 100)
			{
				if (currentRotation < 315 && currentRotation > 135)
				{
					currentRotation += rotationSpeed * fixedDeltaTime;
				}
				else
				{
					currentRotation -= rotationSpeed * fixedDeltaTime;
				}
			}
		}
	}

	//cout << "Angle : " << currentRotation << '\n';
	tankSprite.setRotation(currentRotation);
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
void Player::setRotationSpeed(float value)
{
	rotationSpeed = value;
}
void Player::defaultBoxColliderOffset()
{
	boxColliderOffset.x = 0;
	boxColliderOffset.y = 0;
}
