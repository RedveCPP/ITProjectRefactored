#pragma once
#include "Shape.hpp"

class Circle :public virtual Shape
{
private:
	Vec2 _center;
	int _radius;
public:
	Circle(const Vec2& position, int radius, int index);
	virtual ~Circle() { fillColor = deleteColor; };
	virtual void Draw(sf::RenderWindow& window);
};

Circle::Circle(const Vec2& position, int radius, int index):
	_center{position},
	_radius{radius}
{
	shapeIndex = index;
}

void Circle::Draw(sf::RenderWindow& window)
{
	sf::CircleShape object(static_cast<float>(_radius));
	object.setFillColor(fillColor);
	object.setPosition(static_cast<float>(_center.x - _radius), static_cast<float>(_center.y - _radius));
	window.draw(object);
	PrintIndex(window, _center);
}