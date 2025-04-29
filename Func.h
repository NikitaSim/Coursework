#pragma once

#include <vector>
#include <cmath>
#include "Point.h"

std::vector<Point> convexHull(std::vector<Point>&);
int orientation(const Point&, const Point&, const Point&);