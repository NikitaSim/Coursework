#pragma once

#include <vector>
#include <cmath>
#include "Point.h"


std::vector<Point> convexHull(std::vector<Point>&);
int orientation(const Point&, const Point&, const Point&);
bool SAT(const std::vector<Point>&, const std::vector<Point>&);
std::vector<Point> Normals(const std::vector<Point>& points);
std::vector<min_max_proj> min_maxProjection(const std::vector<Point>&, const std::vector<Point>&);