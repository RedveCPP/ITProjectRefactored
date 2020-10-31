#pragma once
#include "Circle.hpp"
#include "Triangle.hpp"
#include "Square.hpp"
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Image.hpp>

int GetFirstFreeField(Shape** arrayPtr, size_t arraySize)
{
	for (int i = 0; i < arraySize; ++i) { if (!arrayPtr[i]) { return i; } }
	return -1;
}

#include <Windows.h>
void AddANewShape(Shape** arrayPtr, size_t arraySize)
{
	system("cls");
	short int userDecision = 0;
	int freeShapeIndex = GetFirstFreeField(arrayPtr, arraySize);
	if (freeShapeIndex < 0)
	{
		std::cout << "There is no free space" << std::endl;
		return;
	}

	while(userDecision!=1&&userDecision!=2&&userDecision!=3&&userDecision!=4)
	{
		system("cls");
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
			break;
		}
		break;
		case 2:
		{
			std::cout << "Enter center point and radius, for ex. 400 300 50" << std::endl;
			int x, y, r;
			std::cin >> x >> y >> r;
			arrayPtr[freeShapeIndex] = new Circle(Vec2(x, y), r, freeShapeIndex);
			break;
		}
		break;
		case 3:
		{
			{
				std::cout << "Enter 2 points (x,y) that will be corners. for ex 400 300 5 15" << std::endl;
				int x1, x2;
				int y1, y2;
				std::cin >> x1 >> y1 >> x2 >> y2;
				// 8 FUCKING HOURS WITH RECTANGLE CLASS BUG, AND THE FUCKING PROBLEM WAS FUCKING NAME THAT DONT REPEAT IN ENTIRE FUCKING SOLUTION
				arrayPtr[freeShapeIndex] = new Square(Vec2(x1, y1), Vec2(x2, y2), freeShapeIndex);
			}
			break;
		}
		break;
		case 4:
			break;
		default:
			std::cout << "Choose another option" << std::endl;
			continue;
		}
	}
}

void DeleteAShape(Shape** arrayPtr, size_t arraySize)
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

#include <SFML/Audio.hpp>
#include <chrono>
#include <random>
#include <cmath>
void EasterEgg(sf::RenderWindow& window, sf::Event& event)
{
	sf::Text instructions;
	sf::Font font;
	if (!font.loadFromFile("Arial.ttf")) { throw("Couldn't load font"); }
	instructions.setFillColor(sf::Color::Black);
	instructions.setFont(font);
	instructions.setCharacterSize(25);
	instructions.setString("Press N to break");
	instructions.setOutlineThickness(2);
	instructions.setOutlineColor(sf::Color::White);
	instructions.setPosition(10, 10);
	sf::Music music;
	if (!music.openFromFile("music.ogg"))	// 31s
	{
		std::cerr << "Error with loading music file" << std::endl;
		return;
	}
	system("cls");
	sf::Texture graphText;
	sf::Texture urbanTxt;
	if (!urbanTxt.loadFromFile("urban.jpg")) {}
	if (!graphText.loadFromFile("wykres.png")) {}
	else
	{
		music.setVolume(70);
		music.play();
		std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
		std::chrono::steady_clock::time_point end;
		sf::Sprite graph;
		sf::Sprite urbanBackground;
		graph.setTexture(graphText);
		graph.setScale(sf::Vector2f(static_cast<float>(1.0 * window.getSize().x / 675), static_cast<float>(1.0 * window.getSize().y / 375)));
		urbanBackground.setTexture(urbanTxt);
		urbanBackground.setScale(static_cast<float>(1.0*window.getSize().x / 960), static_cast<float>(1.0*window.getSize().y / 847));
		urbanBackground.setPosition(sf::Vector2f(0, 0));
		while (std::chrono::duration_cast<std::chrono::seconds> (end - begin).count() <= 31)
		{
			end = std::chrono::steady_clock::now();
			if (std::chrono::duration_cast<std::chrono::milliseconds> (end - begin).count() >= 6500)
			{
				music.setVolume(100);
				static int seed = 0;
				seed++;
				std::mt19937 engine;
				const short unsigned int range{ 7 };
				std::uniform_int_distribution<int> distributor(-range, range);
				engine.seed(seed);
				int x = distributor(engine);
				int y = distributor(engine);
				graph.setPosition(static_cast<float>(0.1 * window.getSize().x + x), static_cast<float>(0.1 * window.getSize().y + y + 20));
				sf::Color recColor = sf::Color(255, 0, 0,200);
				window.draw(urbanBackground);
				sf::RectangleShape rec;
				rec.setPosition(sf::Vector2f(0, 0));
				rec.setSize(sf::Vector2f(window.getSize().x,window.getSize().y));
				rec.setFillColor(recColor);
				window.draw(rec);
				window.draw(instructions);
				window.draw(graph);
			}
			
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::N)) { return; }
			while (window.pollEvent(event)) {}
			window.display();
		}
	}
}

void MenuEvents(sf::Event& event, Shape** shapeArray, size_t arraySize, sf::RenderWindow& window, sf::Text& text)
{
	if (event.type == event.Closed) { window.close(); }
	if (event.type == event.KeyPressed)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1)) { AddANewShape(shapeArray, arraySize); }
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2)) { DeleteAShape(shapeArray, arraySize); }
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num3)) { window.close(); }
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::M)) { EasterEgg(window, event); }
	}
}

void SetWindowAndConsolePosition(sf::RenderWindow& window)
{
	const unsigned int screenSizeX{ sf::VideoMode::getDesktopMode().width };
	const unsigned int screenSizeY{ sf::VideoMode::getDesktopMode().height };
	int x = screenSizeX / 2;
	int y = screenSizeY / 2;
	window.create(sf::VideoMode(x, y), "IT works");
	window.setPosition(sf::Vector2i(5, 5));
	HWND consoleWindow = GetConsoleWindow();
	SetWindowPos(consoleWindow, 0, x + 10, 5, screenSizeX - 5 - (x + 5), y, SWP_SHOWWINDOW);
}