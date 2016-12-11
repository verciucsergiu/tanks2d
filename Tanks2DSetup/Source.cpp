#include "SFML\Graphics.hpp"
#include <iostream>

using namespace sf;
using namespace std;

int main(int argc, char ** argv)
{
	//WINOW W/O RESIZE MODE
	sf::RenderWindow renderWindow(sf::VideoMode(800, 600), "Tanks", sf::Style::Titlebar | sf::Style::Close);
	cout << "window is open!\n";
	//renderWindow.setPosition(Vector2i(10, 50));
	
	sf::Clock clock;

	renderWindow.setFramerateLimit(30);

	while (renderWindow.isOpen())
	{
		
		sf::Event event;
		while (renderWindow.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				renderWindow.close();
				cout << "window is closed!\n";
			}
		}
		sf::Time time = clock.getElapsedTime();
		cout <<1.0f / time.asSeconds() << '\n';
		clock.restart().asSeconds();

		renderWindow.clear();
		renderWindow.display();
	}
}