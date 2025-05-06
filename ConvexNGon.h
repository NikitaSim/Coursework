#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "Point.h"

class Point;

class ConvexNGon {
private:
	int sides;
	float maxRadius;
	std::vector<Point> hull; // Указан тип
public:
	ConvexNGon(int s, float r) : sides(s), maxRadius(r){}

	sf::ConvexShape createConvexNGon(sf::Vector2f position);

	void change_SideAndRadius(int, float);

	std::vector<Point> getHullPoints();

	~ConvexNGon();

};