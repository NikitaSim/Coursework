#pragma once
#include "ConvexNGon.h"

struct min_max_proj {
	float minProj,maxProj;
};

class Point {
private:
	float x,y;
	float angle;
	float radius;
public:
	// ����������� �� ���������
	Point() : x(0), y(0), angle(0), radius(0) {}
	Point(float x, float y, float ang, float r) : x(x), y(y), angle(ang), radius(r){}
	Point(float x, float y) : x(x), y(y), angle(0), radius(0){}

	friend int orientation(const Point&, const Point&, const Point&);
	friend std::vector<Point> convexHull(std::vector<Point>&);
	friend class ConvexNGon;
	friend int main();
	friend std::vector<Point> Normals(const std::vector<Point>&);
	friend bool SAT(const std::vector<Point>& points_1, const std::vector<Point>& points_2);
	friend std::vector<min_max_proj> min_maxProjection(
		const std::vector<Point>& points,
		const std::vector<Point>& normal);
};