#include <iostream>
#include "Shape.hpp"
#include <SFML/Graphics.hpp>
#include "MainFunctions.hpp"

int main()
{
	Shape* shapeArray[20]{ nullptr };
	sf::RenderWindow window(sf::VideoMode(800, 600), "IT Project");
	sf::Event event;
	sf::Text instruction;
	while (window.isOpen())
	{
		window.clear(sf::Color(46, 46, 46));
		SetTextOnScreen(window);
		while (window.pollEvent(event)) { MenuEvents(event, shapeArray, 20, window, instruction); }
		for (int i = 0; i < 20; ++i) { if (shapeArray[i]) { shapeArray[i]->Draw(window); } }
		window.draw(instruction);
		window.display();
	}
	for (int i = 0; i < 20; ++i) { delete shapeArray[i]; }
	return 0;
}