#include "hud.h"



hud::hud()
{
	if (!font.loadFromFile("hud.otf"))
	{

	}
}


hud::~hud()
{

}

void hud::draw(sf::RenderWindow & window)
{
	textHealth.setFont(font);
	sf::String healthString = to_string(health);
	textHealth.setString(healthString);
	textHealth.setCharacterSize(35);
	textHealth.setColor(sf::Color::Red);
	textHealth.setOutlineColor(sf::Color::Black);
	textHealth.setOutlineThickness(2);
	textHealth.setScale(1.2f, .8f);
	textHealth.setPosition(window.getView().getCenter().x - window.getSize().x / 2 + 15, window.getView().getCenter().y - window.getSize().y / 2);
	window.draw(textHealth);
}
