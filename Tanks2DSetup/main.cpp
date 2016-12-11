#include "SFML\Graphics.hpp"
#include <iostream>

using namespace sf;
using namespace std;

int main(int argc,char ** argv)
{
	
	RenderWindow renderWindow(VideoMode(640, 480),"Tanks");
	cout << "window is open!\n";
	//renderWindow.setPosition(Vector2i(10, 50));
	while (renderWindow.isOpen())
	{
		renderWindow.clear();
		renderWindow.display();
		Event event;
		while (renderWindow.pollEvent(event))
		{
			if (event.type == Event::Closed)
			{
				renderWindow.close();
				cout << "window is closed!\n";
			}
		}
	}
}