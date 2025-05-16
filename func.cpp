#include <algorithm>
#include <iostream>
#include "Func.h"
#include "ConvexNGon.h"
#include "math.h"

// Алгоритм Грэхема для выпуклой оболочки
std::vector<Point> convexHull(std::vector<Point>& points) {
	int n = points.size();
	if (n < 3) return {};

	// Находим самую нижнюю (и левую при равенстве) точку
	int min_idx = 0;
	for (int i = 1; i < n; i++) {
		if (points[i].y < points[min_idx].y ||
			(points[i].y == points[min_idx].y && points[i].x < points[min_idx].x))
			min_idx = i;
	}
	std::swap(points[0], points[min_idx]);

	// Сортируем остальные точки по полярному углу относительно начальной
	Point p0 = points[0];
	std::sort(points.begin() + 1, points.end(), [p0](const Point& a, const Point& b) {
		float angleA = atan2(a.y - p0.y, a.x - p0.x);
		float angleB = atan2(b.y - p0.y, b.x - p0.x);
		return angleA < angleB;
		});

	// Строим выпуклую оболочку
	std::vector<Point> hull;
	hull.push_back(points[0]);
	hull.push_back(points[1]);
	hull.push_back(points[2]);

	for (int i = 3; i < n; i++) {
		while (orientation(hull[hull.size() - 2], hull.back(), points[i]) != 2)		//return (val > 0) ? 1 : 2;    // 1 - по часовой, 2 - против
			hull.pop_back();
		hull.push_back(points[i]);
	}

	if (hull.size() < 3) {
		throw std::runtime_error("Convex hull requires at least 3 points");
	}

	return hull;//points;
}

int orientation(const Point& p, const Point& q, const Point& r) {
	float val = (q.y - p.y) * (r.x - q.x) - (q.x - p.x) * (r.y - q.y);
	if (val == 0) return 0;      // коллинеарные
	return (val > 0) ? 1 : 2;    // 1 - по часовой, 2 - против
}

//struct min_max_proj {
//	float minProj;
//	float maxProj;
//};

bool SAT(const std::vector<Point>& points_1, const std::vector<Point>& points_2) {

	if (points_1.empty() || points_2.empty()) return 0.0f;

	std::vector<Point> normals_1 = Normals(points_1);
	std::vector<Point> normals_2 = Normals(points_2);

	std::vector<Point> Normal_axis = normals_1;
	Normal_axis.insert(Normal_axis.end(), normals_2.begin(), normals_2.end());
	//объеденить нормали(оси) убрать повторяющиеся 
	// Удаление дубликатов нормалей
	std::sort(Normal_axis.begin(), Normal_axis.end(), [](const Point& a, const Point& b) {
		return a.x < b.x || (a.x == b.x && a.y < b.y);
		});
	auto last = std::unique(Normal_axis.begin(), Normal_axis.end(),
		[](const Point& a, const Point& b) {
			return std::abs(a.x - b.x) < 1e-3 && std::abs(a.y - b.y) < 1e-3;
		});
	Normal_axis.erase(last, Normal_axis.end());

	if (Normal_axis.empty()) return 0.0f;

	//массивы структур
	std::vector<min_max_proj> min_maxProj_shape_1 = min_maxProjection(points_1, Normal_axis);
	std::vector<min_max_proj> min_maxProj_shape_2 = min_maxProjection(points_2, Normal_axis);

	//пересечение фигур

	float min_distance = std::numeric_limits<float>::infinity();
	bool is_intersecting = false;//true // Предполагаем, что фигуры пересекаются

	for (size_t i = 0; i < Normal_axis.size(); i++) {
		float overlap_start = std::max(min_maxProj_shape_1[i].minProj, min_maxProj_shape_2[i].minProj);
		float overlap_end = std::min(min_maxProj_shape_1[i].maxProj, min_maxProj_shape_2[i].maxProj);

		// Если проекции НЕ перекрываются на этой оси
		if (overlap_start > overlap_end) {
			/*float distance = overlap_start - overlap_end;
			if (distance < min_distance) {
				min_distance = distance;
				std::cout << "New min distance on axis (" << Normal_axis[i].x << ", " << Normal_axis[i].y << "): " << distance << std::endl;
			}*/
			is_intersecting = true;//false // Найдена разделяющая ось
		}
	}

	return is_intersecting;
}


std::vector<Point> Normals(const std::vector<Point>& points) {

	std::vector<Point> normals;

	for (int i = 0; i < points.size(); i++) {

		float x = points[(i + 1) % points.size()].x - points[i].x;
		float y = points[(i + 1) % points.size()].y - points[i].y;

		Point normal = { -y,x };

		float length = std::sqrt(normal.x * normal.x + normal.y * normal.y);
		if (length != 0) {
			normal.x /= length;
			normal.y /= length;
		}

		std::cout << "Normal " << i << ": (" << normal.x << ", " << normal.y << ")\n";
		normals.push_back(normal);
	}
	return normals;
}

std::vector<min_max_proj> min_maxProjection(
	const std::vector<Point>& points,
	const std::vector<Point>& normal) {

	std::vector<min_max_proj> results;

	for (const auto axis : normal) {
		if (points.empty()) {
			results.push_back({ 0,0 });
			continue;
		}

		float min_proj = points[0].x * axis.x + points[0].y * axis.y;
		float max_proj = min_proj;

		for (size_t i = 0; i < points.size(); i++) {
			float proj = points[i].x * axis.x + points[i].y * axis.y;
			if (proj < min_proj) min_proj = proj;
			if (proj > max_proj) max_proj = proj;
		}

		std::cout << "Axis (" << axis.x << ", " << axis.y << "): min=" << min_proj << ", max=" << max_proj << "\n";

		results.push_back({ min_proj ,max_proj });
	}
	return results;
}