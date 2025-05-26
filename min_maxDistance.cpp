#include "Point.h"
#include "min_maxDistance.h"
#include <vector>
#include <iostream>

class Point;

Distance minDistance(const std::vector<Point>& shape_1, const std::vector<Point>& shape_2) {
	if (shape_1.empty() || shape_2.empty()) {
		return { 0.0f, Point(), Point() }; // Корректная инициализация
	}

	float min_sq = std::numeric_limits<float>::max();
	Point start = shape_1[0];
	Point end = shape_2[0];

	for (const auto& p1 : shape_1) {
		for (const auto& p2 : shape_2) {
			const float dx = p2.x - p1.x;
			const float dy = p2.y - p1.y;
			const float sq_dist = dx * dx + dy * dy;

			if (sq_dist < min_sq) {
				min_sq = sq_dist;
				start = p1;
				end = p2;
			}
		}
	}

	// Вывод информации (опционально)
	std::cout << "shape 1 X: " << start.x << " Y: " << start.y << "\n"
		<< "shape 2 X: " << end.x << " Y: " << end.y << std::endl;

	return { std::sqrt(min_sq), start, end }; // Возврат структуры
}

Distance maxDistance(const std::vector<Point>& shape_1, const std::vector<Point>& shape_2) {

	if (shape_1.empty() || shape_2.empty()) {
		return { 0.0f, Point(), Point() }; // Корректная инициализация
	}

	float maxlen = std::numeric_limits<float>::lowest();
	float len;
	Point start = shape_1[0];
	Point end = shape_2[0];
	for (const auto& point_1 : shape_1) {
		for (const auto& point_2 : shape_2) {
			float dx = point_2.x - point_1.x;
			float dy = point_2.y - point_1.y;
			float len = dx * dx + dy * dy;
			if (len > maxlen) {
				maxlen = len;
				start = point_1;
				end = point_2;
			}
		}
	}

	std::cout << "shape 1 X: " << start.x << " Y: " << start.y << "\n"
		<< "shape 2 X: " << end.x << "Y: " << end.y << std::endl;

	return { std::sqrt(maxlen), start, end };
}