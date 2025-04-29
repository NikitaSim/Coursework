#include "Func.h"

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

	return hull;
}

int orientation(const Point& p, const Point& q, const Point& r) {
	float val = (q.y - p.y) * (r.x - q.x) - (q.x - p.x) * (r.y - q.y);
	if (val == 0) return 0;      // коллинеарны
	return (val > 0) ? 1 : 2;    // 1 - по часовой, 2 - против
}