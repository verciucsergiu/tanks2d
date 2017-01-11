#pragma once
#include <SFML\Graphics.hpp>
using namespace sf;


class objectsOnMap
{
public:
	objectsOnMap();
	~objectsOnMap();

	Sprite objectSprite;
	void create(int gridX, int gridY, int x, int y, int type);
	void draw(RenderWindow &window);
	Texture objectTexture;
private:
	

};

