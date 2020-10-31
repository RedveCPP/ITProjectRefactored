#include <iostream>
#include "Shape.hpp"
#include <SFML/Graphics.hpp>
#include "MainFunctions.hpp"

int main()
{
	std::cout << "How big shape array do you want?"<<std::endl;
	size_t sizeOfArray;
	std::cin >> sizeOfArray;
	system("cls");
	sf::RenderWindow window(sf::VideoMode(640, 480), "IT Project");
	SetWindowAndConsolePosition(window);
	sf::Event event;
	sf::Text instruction;
	Shape** shapeArray = new Shape * [sizeOfArray] {};
	while (window.isOpen())
	{
		window.clear(sf::Color(46, 46, 46));
		SetTextOnScreen(window);
		while (window.pollEvent(event)) { MenuEvents(event, shapeArray, sizeOfArray, window, instruction); }
		for (int i = 0; i < sizeOfArray; ++i) { if (shapeArray[i]) { shapeArray[i]->Draw(window); } }
		window.draw(instruction);
		window.display();
	}
	for (int i = 0; i < sizeOfArray; ++i) { delete shapeArray[i]; }
	delete[]shapeArray;
	return 0;
}