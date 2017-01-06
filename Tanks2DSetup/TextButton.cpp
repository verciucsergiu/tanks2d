#include "TextButton.h"



TextButton::TextButton()
{
	aviable = true;
}


TextButton::~TextButton()
{
}

void TextButton::Draw(RenderWindow &window)
{
	if (!aviable)
	{
		Color lowOpacity(255, 35, 25, 85);
		buttonSprite.setColor(lowOpacity);
		textDisplay.setFillColor(lowOpacity);
	}
	window.draw(buttonSprite);
	window.draw(textDisplay);
}

bool TextButton::checkClick(int x, int y)
{
	Vector2f point(x, y);
	return buttonSprite.getGlobalBounds().contains(point);
}

void TextButton::checkHover(int x, int y, RenderWindow &window)
{
	if (aviable)
	{
		if (checkClick(x, y))
		{
			Color lowOpacity(255, 255, 255, 100);
			buttonSprite.setColor(lowOpacity);
		}
		else
		{
			Color highOpacity(255, 255, 255, 255);
			buttonSprite.setColor(highOpacity);
		}
	}
	else
	{
		if (checkClick(x, y))
		{
			Text notAviable("This is not aviable!",font);
			notAviable.setCharacterSize(15);
			float xOriginText = notAviable.getGlobalBounds().width / 2;
			float yOriginText = notAviable.getGlobalBounds().height / 2;
			notAviable.setOrigin(xOriginText, yOriginText);
			notAviable.setPosition(buttonSprite.getPosition().x, buttonSprite.getPosition().y - buttonSprite.getGlobalBounds().height / 2 - 8);
			notAviable.setColor(Color::Red);
			window.draw(notAviable);
		}
	}
	
	
}

void TextButton::setActive(bool value)
{
	aviable = value;
}

bool TextButton::isActive()
{
	return aviable;
}

void TextButton::create(string text, int positionX, int positionY, Color color,sizeType value)
{
	font.loadFromFile("sansation.ttf");
	textDisplay.setFont(font);
	String sfml_text = text;
	textDisplay.setString(sfml_text);
	textDisplay.setCharacterSize(30);
	textDisplay.setColor(color);	
	switch (value)
	{
	case small:
		if (!buttonTexture.loadFromFile("sprites/button_small.png"))
		{
			cout << "Error!";
		}
		break;
	case mediu:
		if (!buttonTexture.loadFromFile("sprites/button.png"))
		{
			cout << "Error!";
		}
		break;
	case large:
		break;
	default:
		break;
	}
	
	buttonSprite.setTexture(buttonTexture);
	float xOrigin = buttonSprite.getGlobalBounds().width / 2;
	float yOrigin = buttonSprite.getGlobalBounds().height / 2 - 5;
	buttonSprite.setOrigin(xOrigin, yOrigin);
	float xOriginText = textDisplay.getGlobalBounds().width / 2;
	float yOriginText = textDisplay.getGlobalBounds().height / 2;
	textDisplay.setOrigin(xOriginText, yOriginText);
	textDisplay.setPosition(positionX, positionY);
	buttonSprite.setPosition(positionX, positionY);
}
