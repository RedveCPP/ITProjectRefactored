#pragma once
#include <SFML/Graphics.hpp>

struct Vec2
{
	int x, y;
	Vec2(int _x = 0, int _y = 0) { x = _x; y = _y; }
};

class Shape
{
protected:
	int shapeIndex{};
	sf::Color deleteColor{ 46,46,46 };
	sf::Color createColor{ sf::Color::White };
	sf::Color fillColor{ createColor };
	void PrintIndex(sf::RenderWindow& window,const Vec2& position);
public:
	virtual void Draw(sf::RenderWindow& window) = 0;
	virtual ~Shape() {}
};

void Shape::PrintIndex(sf::RenderWindow& window, const Vec2& position)
{
	sf::Text number;
	sf::Font font;
	if (!font.loadFromFile("Arial.ttf")) { return; }
	number.setFillColor(sf::Color::Red);
	number.setFont(font);
	number.setCharacterSize(25);
	number.setString(std::to_string(shapeIndex));
	number.setOutlineThickness(2);
	number.setOutlineColor(sf::Color::Black);
	number.setPosition(static_cast<float>(position.x - 12), static_cast<float>(position.y - 12));
	window.draw(number);
}