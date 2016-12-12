#include "SFML\Graphics.hpp"
#include <iostream>
#include <fstream>
#include <cctype>
#include "Player.h"

using namespace std;

int main(int argc, char ** argv)
{
	//WINOW W/O RESIZE MODE
	sf::RenderWindow renderWindow(sf::VideoMode(800, 600), "Tanks", sf::Style::Titlebar | sf::Style::Close);
	cout << "window is open!\n";
	//renderWindow.setPosition(Vector2i(10, 50));
	Player player;
	sf::Clock clock;
	renderWindow.setFramerateLimit(30);
	player.transform(400, 300);
	player.setScale(2, 2);
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


		// functia asta se apeleaza la fiecare frame
		player.update(time.asSeconds(),renderWindow);
		clock.restart().asSeconds();

		renderWindow.clear();
		
		
		player.draw(renderWindow);
		renderWindow.display();
	}
}