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
	else
	{
		Color lowOpacity(255, 35, 25, 255);
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
			Text notAvailable("This is not available!",font);
			notAvailable.setCharacterSize(17);
			notAvailable.setStyle(Text::Style::Bold);
			float xOriginText = notAvailable.getGlobalBounds().width / 2;
			float yOriginText = notAvailable.getGlobalBounds().height / 2;
			notAvailable.setOrigin(xOriginText, yOriginText);
			notAvailable.setPosition(buttonSprite.getPosition().x, buttonSprite.getPosition().y - buttonSprite.getGlobalBounds().height / 2 - 12);
			notAvailable.setColor(Color::Black);
			window.draw(notAvailable);
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
		if (!buttonTexture.loadFromFile("sprites/button_large.png"))
		{
			cout << "Error!";
		}
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
