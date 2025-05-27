#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "Point.h"

class Point;

class ConvexNGon {
private:
	int sides;
	float maxRadius;
	std::vector<Point> hull;
public:
	ConvexNGon(int s, float r) : sides(s), maxRadius(r){}
	ConvexNGon():sides(0), maxRadius(0.f){}

	sf::ConvexShape createConvexNGon(sf::Vector2f position);
	sf::ConvexShape createConvexNGonOwnPoints(sf::Vector2f, const std::vector<Point>&);

	void change_SideAndRadius(int, float);

	std::vector<Point> getHullPoints();

	~ConvexNGon();

};