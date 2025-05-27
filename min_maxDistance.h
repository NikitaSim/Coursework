#pragma once
#include "Point.h"
#include <vector>

//class Point;

struct Distance {
    float length;
    Point start_point;
    Point end_point;

    Distance(float len = 0.0f, Point start = Point(), Point end = Point())
        : length(len), start_point(start), end_point(end) {
    }
};

Distance minDistance(const std::vector<Point>&, const std::vector<Point>&);
Distance maxDistance(const std::vector<Point>&, const std::vector<Point>&); // Теперь это две разные функции