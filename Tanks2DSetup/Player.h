#pragma once
#include <SFML\Graphics.hpp>

class Player
{
public:
	Player();
	~Player();
	/*float scale;*/
	void update(float dt, sf::RenderWindow &window);
	void draw(sf::RenderWindow &window);
	void transform(float coordonataX,float coordonataY);
	void destroy();
	bool collision(sf::Vector2i position);
	void lookAt(sf::Vector2i target,sf::RenderWindow &window);
	void setScale(float x, float y);
	
private:
	sf::Sprite tankSprite;
	sf::Texture tankTexture;
	sf::Sprite barrelSprite;
	sf::Texture barrelTexture;
	/*bool setScale;*/
};

