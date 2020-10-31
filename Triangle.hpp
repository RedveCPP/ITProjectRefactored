#pragma once
#include "Shape.hpp"
#include <array>

class Triangle :public virtual Shape
{
private:
	std::array<Vec2, 3> triangleCorners;
	// to print number on center of triangle
	Vec2 center;
	Vec2 GetCenter();
public:
	Triangle(const Vec2& p1, const Vec2& p2, const Vec2& p3, int index);
	virtual ~Triangle() { fillColor = deleteColor; }
	virtual void Draw(sf::RenderWindow& window);
	
};

Triangle::Triangle(const Vec2& p1, const Vec2& p2, const Vec2& p3, int index)
{
	triangleCorners[0] = p1;
	triangleCorners[1] = p2;
	triangleCorners[2] = p3;
	center = GetCenter();
	shapeIndex = index;
}

Vec2 Triangle::GetCenter()
{
	int x = (triangleCorners[0].x + triangleCorners[1].x + triangleCorners[2].x) / 3;
	int y = (triangleCorners[0].y + triangleCorners[1].y + triangleCorners[2].y) / 3;
	return Vec2(x, y);
}

void Triangle::Draw(sf::RenderWindow& window)
{
	for (int i = 0; i < 3; ++i)
	{
		sf::Vertex Line[2]{
			sf::Vertex(sf::Vector2f(static_cast<float>(triangleCorners[i].x),static_cast<float>(triangleCorners[i].y))),
			sf::Vertex(sf::Vector2f(static_cast<float>(triangleCorners[(i+1)%3].x),static_cast<float>(triangleCorners[(i + 1) % 3].y)))
		};
		window.draw(Line, 2, sf::Lines);
	}
	PrintIndex(window, center);
}