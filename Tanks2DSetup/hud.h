#pragma once
#include <SFML\Graphics.hpp>
#include <string>
using namespace std;
class hud
{
public:
	hud();
	~hud();
	int health;
	int timer;
	void draw(sf::RenderWindow &window);
private:
	sf::Text textHealth;
	sf::Font font;
};

