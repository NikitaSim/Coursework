#include <SFML/Graphics.hpp>
#include <cmath>
#include <algorithm>
#include <vector>
#include <random>
#include <ctime>

struct Point {
	float x;
	float y;
	float angle;
	float radius;
};

// Найти ориентацию тройки точек (p, q, r)
int orientation(const Point& p, const Point& q, const Point& r) {
	float val = (q.y - p.y) * (r.x - q.x) - (q.x - p.x) * (r.y - q.y);
	if (val == 0) return 0;      // коллинеарны
	return (val > 0) ? 1 : 2;    // 1 - по часовой, 2 - против
}

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

sf::ConvexShape createConvexNGon(int sides, float maxRadius, sf::Vector2f position) {

	sf::ConvexShape polygon;
	std::vector<Point> points;

	// рандомайзер
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<> angleDist(0.0, 2 * 3.14159265);
	std::uniform_real_distribution<> radiusDist(maxRadius * 0.5, maxRadius);

	// Генерация случайных точек
	for (int i = 0; i < sides; ++i) {
		float angle = angleDist(gen);
		float radius = radiusDist(gen);
		points.push_back({
			radius * cos(angle),
			radius * sin(angle),
			angle,
			radius
			});
	}

	// Построение выпуклой оболочки
	std::vector<Point> hull = convexHull(points);
	if (hull.size() < 3) return polygon; // Защита от ошибок

	// Настройка многоугольника
	polygon.setPointCount(hull.size());
	for (size_t i = 0; i < hull.size(); ++i) {
		polygon.setPoint(i, { hull[i].x, hull[i].y });
	}

	polygon.setPosition(position);
	polygon.setOrigin(0, 0);
	return polygon;
}

int main() {
	sf::RenderWindow window(sf::VideoMode(800, 600), "Convex NGon");
	window.setFramerateLimit(60);

	srand(time(0));
	int side = rand() % (15 - 3 + 1) + 3;

	sf::ConvexShape shape_1 = createConvexNGon(side, 100.f, { 250, 300 });
	shape_1.setFillColor(sf::Color::Cyan);
	shape_1.setOutlineThickness(2.f);
	shape_1.setOutlineColor(sf::Color::Red);

	sf::ConvexShape shape_2 = createConvexNGon(side, 100.f, { 550, 300 });
	shape_1.setFillColor(sf::Color::Green);
	shape_1.setOutlineThickness(2.f);
	shape_1.setOutlineColor(sf::Color::Yellow);

	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				window.close();
			if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::R) {
				side = rand() % (15 - 3 + 1) + 3;
				shape_1 = createConvexNGon(side, 100.f, { 250, 300 });
				shape_1.setFillColor(sf::Color::Cyan);
				shape_1.setOutlineThickness(2.f);
				shape_1.setOutlineColor(sf::Color::Red);
			}

			if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::T) {
				side = rand() % (15 - 3 + 1) + 3;
				shape_2 = createConvexNGon(side, 100.f, { 550, 300 });
				shape_2.setFillColor(sf::Color::Green);
				shape_2.setOutlineThickness(2.f);
				shape_2.setOutlineColor(sf::Color::Yellow);
			}
		}

		window.clear(sf::Color::Black);
		window.draw(shape_1);
		window.draw(shape_2);
		window.display();
	}

	return 0;
}