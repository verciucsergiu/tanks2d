#include "Player.h"
#include <iostream>

using namespace std;


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
	tankSprite.setOrigin(x, y);
	x += 3;
	barrelSprite.setOrigin(x, y);
	
}

Player::~Player()
{
	cout << "Player destroyed!";
}
void Player::update(float dt,sf::RenderWindow &window)
{
	sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
	lookAt(mousePosition, window);
}
void Player::draw(sf::RenderWindow &window)
{	
	
	window.draw(tankSprite);
	window.draw(barrelSprite);
}
void Player::transform(float coordonataX,float coordonataY)
{
	sf::Vector2f position = sf::Vector2f(coordonataX, coordonataY);
	tankSprite.setPosition(position);
	barrelSprite.setPosition(position);
}
void Player::destroy()
{
	sf::Color color = sf::Color(0.f, 0.f, 0.f, 0.f);
	tankSprite.setColor(color);
}
bool Player::collision(sf::Vector2i position)
{
	return false;
}

void Player::lookAt(sf::Vector2i target, sf::RenderWindow &window)
{
	sf::Vector2f curPos = barrelSprite.getPosition();

	const float PI = 3.14159265;

	float dx = curPos.x - target.x;
	float dy = curPos.y - target.y;

	float rotation = (atan2(dy, dx)) * 180 / PI;

	barrelSprite.setRotation(rotation);
}
void Player::setScale(float x, float y)
{
	barrelSprite.setScale(x, y);
	tankSprite.setScale(x, y);
}