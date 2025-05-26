#pragma once
//#include "ConvexNGon.h"
//#include "min_maxDistance.h"
#include <vector>

struct Distance;

struct min_max_proj {
	float minProj;
	float maxProj;
};

class Point {
private:
	float x,y;
	float angle;
	float radius;
public:
	// Конструктор по умолчанию
	Point() : x(0), y(0), angle(0), radius(0) {}
	Point(float x, float y, float ang, float r) : x(x), y(y), angle(ang), radius(r){}
	Point(float x, float y) : x(x), y(y), angle(0), radius(0){}
	//конструктор копирования

	friend int orientation(const Point&, const Point&, const Point&);
	friend std::vector<Point> convexHull(std::vector<Point>&);
	friend class ConvexNGon;
	friend class Line;
	friend int main();
	friend std::vector<Point> Normals(const std::vector<Point>&);
	friend bool SAT(const std::vector<Point>&, const std::vector<Point>&);
	friend std::vector<min_max_proj> min_maxProjection(
		const std::vector<Point>&,
		const std::vector<Point>&);
	friend Distance minDistance(const std::vector<Point>&, const std::vector<Point>&);
	friend Distance maxDistance(const std::vector<Point>&, const std::vector<Point>&);
};

