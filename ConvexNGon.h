#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "Point.h"

class ConvexNGon {
private:
	int sides;
	float maxRadius;
	//std::vector<Point> hull_points;
public:
	ConvexNGon(int s, float r) : sides(s), maxRadius(r){}
	sf::ConvexShape createConvexNGon(sf::Vector2f position);
	void change_side(int);
};