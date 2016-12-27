#include "Player.h"
float PI = 3.14159265;
bool show = false;

Player::Player()
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
	x +=5;
	barrelSprite.setOrigin(x, y); // setare pivot centru x+3 scop = rotire corecta a turelei	
}

Player::~Player()
{
	cout << "Player destroyed!";
}

void Player::update(float deltaTime,RenderWindow &window)
{
	int dirX = 0;
	int dirY = 0;

	Vector2i mousePosition = Mouse::getPosition(window);
	lookAt(mousePosition);

	Vector2i movement(0,0);

	if (Keyboard::isKeyPressed(Keyboard::W))
	{
		dirY = -1;
		movement.y -= 1;
	}
	if (Keyboard::isKeyPressed(Keyboard::A))
	{
		dirX = -1;
		movement.x -= 1;
	}
	if (Keyboard::isKeyPressed(Keyboard::S))
	{
		dirY = 1;
		movement.y += 1;
	}
	if (Keyboard::isKeyPressed(Keyboard::D))
	{
		dirX = 1;
		movement.x += 1;
	}



	tankSprite.move(movement.x * deltaTime * speed, movement.y * deltaTime * speed);
	barrelSprite.move(movement.x * deltaTime * speed, movement.y * deltaTime * speed);

	direction.x = dirX;
	direction.y = dirY;

	if (Mouse::isButtonPressed(Mouse::Button::Left))
	{
		//cout << "Fired : (" << barrelSprite.getPosition().x << "," << barrelSprite.getPosition().y << ")\n";
		bullet bulletFired;
		bulletFired.setPosition(barrelSprite.getPosition().x,barrelSprite.getPosition().y);
		bulletFired.Update(deltaTime, window);
	}
	
}
void Player::checkCollision(Sprite wallSprites[], int nrOfWalls)
{

	for (int i = 0; i < nrOfWalls; i++)
	{
		FloatRect rect = wallSprites[i].getGlobalBounds();
		if (tankSprite.getGlobalBounds().intersects(rect))
		{
			cout << "hit wall nr : " << i << '\n';
			speed = 0;
		}
		else
		{
			//speed = 150;
		}
	}
}
void Player::draw(RenderWindow &window)
{	
	window.draw(tankSprite);
	window.draw(barrelSprite);
}
void Player::transform(float coordonataX,float coordonataY)
{
	Vector2f position(coordonataX, coordonataY);
	tankSprite.setPosition(position);
	barrelSprite.setPosition(position);
	offset.x = position.x;
	offset.y = position.y;
}
void Player::destroy()
{
	Color color(0.f, 0.f, 0.f, 0.f);
	tankSprite.setColor(color);
}
bool Player::collision(Vector2i position)
{
	return false;
}

void Player::lookAt(Vector2i target)
{
	Vector2f curentPos = barrelSprite.getPosition();

	const float PI = 3.14159265;

	float dx = offset.x - target.x;
	float dy = offset.y - target.y;

	float rotation = (atan2(dy, dx)) * 180 / PI;

	barrelSprite.setRotation(rotation);
}
void Player::setScale(float x, float y)
{
	barrelSprite.setScale(x, y);
	tankSprite.setScale(x, y);
}