#include "Player.h"
#include "bullet.h"

Player::Player()
{
	currentRotation = 0;
	//multe modificari aici
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
	barrelSprite.setOrigin(0, 5); // am adaugat asta pt. ca turela nu statea locului
}

void Player::update(float deltaTime,RenderWindow &window)
{
	fixedDeltaTime = deltaTime;
	Vector2i mousePosition = Mouse::getPosition(window);
	if (fixedDeltaTime!=0)
	{
		lookAt(mousePosition, window);
	}
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

}
bool Player::collisionVertical(float dir)
{
	for (Collider* current=collFirst; current!=nullptr; current=current->next)
	{
		float y = tankSprite.getPosition().y + 17 * dir + boxColliderOffset.y * dir;
		if (current->target.getGlobalBounds().contains(tankSprite.getPosition().x - dir * 16, y))
		{
			return true;
		}
		if (current->target.getGlobalBounds().contains(tankSprite.getPosition().x, y))
		{
			return true;
		}
		if (current->target.getGlobalBounds().contains(tankSprite.getPosition().x + 16 * dir, y))
		{
			return true;
		}
	}
	return false;
}

void Player::setCollider(Collider * First, Collider * Last)
{
	collFirst = First;
	collLast = Last;
}

bool Player::collisionHorizontal(float dir)
{
	for (Collider* current=collFirst;current!=nullptr; current=current->next)
	{
		float x = tankSprite.getPosition().x + 17 * dir + boxColliderOffset.x * dir;
		if (current->target.getGlobalBounds().contains(x, tankSprite.getPosition().y - dir * 16))
		{
			return true;
		}
		if (current->target.getGlobalBounds().contains(x, tankSprite.getPosition().y))
		{
			return true;
		}
		if (current->target.getGlobalBounds().contains(x, tankSprite.getPosition().y + dir * 16))
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
void Player::lookAt(Vector2i target,RenderWindow &window)
{
	Vector2i currentPos =  window.mapCoordsToPixel(barrelSprite.getPosition(),window.getView());
	
	const float PI = 3.14159265;
	float dx = currentPos.x - target.x;
	float dy = currentPos.y  -target.y;

	//am adaugat asta pt ca turela nu urmareste mouse-ul cum trebuie altfel
	dx = -dx; 
	dy = -dy;

	turretRotation = (atan2(dy, dx)) * 180 / PI; 
	//am scos "float rotation" de aici si l-am adaugat in private
	//am nevoie de el in bullet.cpp

	barrelSprite.setRotation(turretRotation);
}


float Player::getTurretRotation()
{
	return turretRotation;
}

bool Player::isAlive()
{
	return alive;
}

void Player::setAlive(bool value)
{
	alive = value;
}

void Player::tankRotation(int dirX, int dirY)
{
	//wtf should i do :('
	int tolarance = 4;
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
			if ((int)currentRotation >= 180 + tolarance || (int)currentRotation <= 180 - tolarance)
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
			if ((int)currentRotation >= 0 + tolarance || (int)currentRotation <= 0 - tolarance)
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
			if ((int)currentRotation >= 90 + tolarance || (int)currentRotation <= 90 - tolarance)
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
			if ((int)currentRotation >= 270 + tolarance || (int)currentRotation <= 270 - tolarance)
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
			if ((int)currentRotation >= 45 + tolarance || (int)currentRotation <= 45 - tolarance)
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
			if ((int)currentRotation >= 135 + tolarance || (int)currentRotation <= 135 - tolarance)
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
			if ((int)currentRotation >= 225 + tolarance || (int)currentRotation <= 225 - tolarance)
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
			if ((int)currentRotation >= 315 + tolarance || (int)currentRotation <= 315 - tolarance)
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
void Player::takeDamage(int value)
{
	
	if (alive) 
	{
		health -= value;
		if (health<=0)
		{
			alive = false;
		}
	}
}
void Player::defaultBoxColliderOffset()
{
	boxColliderOffset.x = 0;
	boxColliderOffset.y = 0;
}
