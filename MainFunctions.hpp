#pragma once
#include "Rectangle.hpp"
#include "Circle.hpp"
#include "Triangle.hpp"

int GetFirstFreeField(Shape** arrayPtr, int arraySize)
{
	for (int i = 0; i < arraySize; ++i) { if (!arrayPtr[i]) { return i; } }
	return -1;
}

#include <Windows.h>
void AddANewShape(Shape** arrayPtr, int arraySize)
{
	system("cls");
	unsigned short int userDecision = 0;
	int freeShapeIndex = GetFirstFreeField(arrayPtr, arraySize);
	if (freeShapeIndex < 0)
	{
		std::cout << "There is no free space" << std::endl;
		return;
	}
	std::cout << "Which shape do you want to add?" << std::endl <<
		"1. Triangle" << std::endl <<
		"2. Circle" << std::endl <<
		"3. Rectangle" << std::endl;
	std::cin >> userDecision;
	switch (userDecision)
	{
	case 1:
	{
		std::cout << "Enter 3 points, for ex. 200 200 250 200 250 300" << std::endl;
		int x[3];
		int y[3];
		std::cin >> x[0] >> y[0] >> x[1] >> y[1] >> x[2] >> y[2];
		arrayPtr[freeShapeIndex] = new Triangle(Vec2(x[0], y[0]), Vec2(x[1], y[1]), Vec2(x[2], y[2]), freeShapeIndex);
	}
	break;
	case 2:
	{
		std::cout << "Enter center point and radius, for ex. 400 300 50" << std::endl;
		int x, y, r;
		std::cin >> x >> y >> r;
		arrayPtr[freeShapeIndex] = new Circle(Vec2(x, y), r, freeShapeIndex);
	}
	break;
	case 3:
	{
		std::cout << "Enter 2 points (x,y) that will be corners. for ex 400 300 5 15" << std::endl;
		int x[2];
		int y[2];
		std::cin >> x[0] >> y[0] >> x[1] >> y[1];
		arrayPtr[freeShapeIndex] = new Rectangle(Vec2(x[0], y[0]), Vec2(x[1], y[1]),freeShapeIndex);
	}
	break;
	default:
		std::cout << "Choose another option" << std::endl;
		break;
	}
}

void DeleteAShape(Shape** arrayPtr, int arraySize)
{
	system("cls");
	short int index = 0;
	std::cout << "Which shape do you want remove?" << std::endl;
	std::cin >> index;
	if (index >= 0 && index <= arraySize)
	{
		if (arrayPtr[index])
		{
			delete arrayPtr[index];
			arrayPtr[index] = nullptr;
		}
		else
		{
			std::cout << "its already eapty";
		}
	}
}

void SetTextOnScreen(sf::RenderWindow& window)
{
	sf::Text instructions;
	sf::Font font;
	if (!font.loadFromFile("Arial.ttf")) { throw("Couldn't load font"); }
	instructions.setFillColor(sf::Color::Black);
	instructions.setFont(font);
	instructions.setCharacterSize(25);
	instructions.setString("Press 1 to add a new shape\nPress 2 to remove a shape\nPress 3 to exit\nPress M to ?");
	instructions.setOutlineThickness(2);
	instructions.setOutlineColor(sf::Color::White);
	instructions.setPosition(10, 10);
	window.draw(instructions);
}

void MenuEvents(sf::Event& event, Shape** shapeArray, int arraySize, sf::RenderWindow& window, sf::Text& text)
{
	if (event.type == event.Closed) { window.close(); }
	if (event.type == event.KeyPressed)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1)) { AddANewShape(shapeArray, arraySize); }
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2)) { DeleteAShape(shapeArray, arraySize); }
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num3)) { window.close(); }
		//if (sf::Keyboard::isKeyPressed(sf::Keyboard::M)) { EasterEgg(window, event); }
	}
}