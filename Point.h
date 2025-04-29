#pragma once
#include "ConvexNGon.h"


class Point {
private:
	float x;
	float y;
	float angle;
	float radius;
public:
	Point(float x, float y, float ang, float r) : x(x), y(y), angle(ang), radius(r){}

	friend int orientation(const Point&, const Point&, const Point&);
	friend std::vector<Point> convexHull(std::vector<Point>&);
	friend class ConvexNGon;
};