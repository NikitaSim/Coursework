#include <SFML/Graphics.hpp>
#include <cmath>
#include <algorithm>
#include <random>
#include <iostream>
#include <vector>
#include "ConvexNGon.h"
#include "Point.h"
#include "Func.h"

sf::ConvexShape ConvexNGon::createConvexNGon(sf::Vector2f position) {
	sf::ConvexShape polygon;
	std::vector<Point> points;

	// рандомойзер
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
	hull = convexHull(points);
	if (hull.size() < 3) return polygon; // Защита от ошибок

	// Настройка многоугольника
	polygon.setPointCount(hull.size());
	for (size_t i = 0; i < hull.size(); ++i) {
		polygon.setPoint(i, { hull[i].x, hull[i].y });
	}

	// Центрируем фигуру
	sf::FloatRect bounds = polygon.getLocalBounds(); //???
	// Учитываем смещение локальных координат
	polygon.setOrigin(bounds.left + bounds.width / 2, bounds.top + bounds.height / 2);
	polygon.setPosition(position);

	return polygon;
}

void ConvexNGon::change_SideAndRadius(int new_side, float new_radius) {
	this->sides = new_side;
	this->maxRadius = new_radius;
}

ConvexNGon::~ConvexNGon() {
	std::cout << "Convex was deleted" << std::endl;
}

std::vector<Point> ConvexNGon::getHullPoints() {
	return hull;
}