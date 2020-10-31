#pragma once
#include "Shape.hpp"

class Rectangle :public virtual Shape
{
private:
	Vec2 corners[2];
	Vec2 GetCenter();
public:
	Rectangle(const Vec2& p1, const Vec2& p2, int index);
	virtual void Draw(sf::RenderWindow& window);
	~Rectangle() { fillColor = deleteColor; }
};

Rectangle::Rectangle(const Vec2& p1, const Vec2& p2, int index)
{
	corners[0] = p1;
	corners[1] = p2;
	if (corners[0].x > corners[1].x) { std::swap(corners[0].x, corners[1].x); }
	if (corners[0].y > corners[1].y) { std::swap(corners[0].y, corners[1].y); }
	shapeIndex = index;
}

Vec2 Rectangle::GetCenter()
{
	int x = (corners[1].x - corners[0].x) / 2 + corners[0].x;
	int y = (corners[1].y - corners[0].y) / 2 + corners[0].y;
	return Vec2(x, y);
}

void Rectangle::Draw(sf::RenderWindow& window)
{
	sf::RectangleShape rectangle;
	rectangle.setFillColor(fillColor);
	rectangle.setPosition(static_cast<float>(corners[0].x), static_cast<float>(corners[0].y));
	rectangle.setSize(sf::Vector2f(static_cast<float>(corners[1].x - corners[0].x), static_cast<float>(corners[1].y - corners[0].y)));
	window.draw(rectangle);
	PrintIndex(window, GetCenter());
}