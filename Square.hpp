#pragma once
#include "Shape.hpp"

class Square :public virtual Shape
{
private:
	Vec2 p1, p2;
	Vec2 GetCenter();
public:
	Square(Vec2&& corner1, Vec2&& corner2, int index);
	virtual void Draw(sf::RenderWindow& window);
	~Square() { fillColor = deleteColor; }
};

Square::Square(Vec2&& corner1, Vec2&& corner2, int index):
	p1{ corner1 },
	p2{ corner2 }
{
	fillColor = createColor;
	shapeIndex = index;
	if (p1.x > p2.x) { std::swap(p1.x, p2.x); }
	if (p1.y > p2.y) { std::swap(p1.y, p2.y); }
}

Vec2 Square::GetCenter()
{	
	int x = (p2.x - p1.x) / 2 + p1.x;
	int y = (p2.y - p1.y) / 2 + p1.y;
	return Vec2(x, y);
}

void Square::Draw(sf::RenderWindow& window)
{
	sf::RectangleShape rectangle;
	rectangle.setFillColor(fillColor);
	rectangle.setPosition(static_cast<float>(p1.x), static_cast<float>(p1.y));
	rectangle.setSize(sf::Vector2f(static_cast<float>(p2.x - p1.x), static_cast<float>(p2.y - p1.y)));
	window.draw(rectangle);
	PrintIndex(window, GetCenter());
}