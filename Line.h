#pragma once

#include <SFML/Graphics.hpp>
#include "Point.h"

class Line {
private:
	Point vertex_start;
	Point vertex_end;
	sf::Color color;
	sf::RectangleShape lineShape;
public:
	Line(const Point& x, const Point& y) : vertex_start(x), vertex_end(y){}
	sf::VertexArray CreateLine() const;
	void updateLine();
	sf::RectangleShape getLine() const;
};