#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "Point.h"

class Point;

class ConvexNGon {
private:
	int sides;
	float maxRadius;
	std::vector<Point> hull; // ”казан тип
public:
	ConvexNGon(int s, float r) : sides(s), maxRadius(r){}
	ConvexNGon():sides(0), maxRadius(0.f){}
	ConvexNGon(const ConvexNGon&& moved) {
		sides = moved.sides;
		maxRadius = moved.maxRadius;
		hull = moved.hull;
		// открыть лекции и написать все 5 конструкторов
	}

	sf::ConvexShape createConvexNGon(sf::Vector2f position);

	void change_SideAndRadius(int, float);

	std::vector<Point> getHullPoints();

	~ConvexNGon();

};