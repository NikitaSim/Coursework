#include <SFML/Graphics.hpp>
#include <algorithm>
#include <ctime>
#include <iostream>
#include "Point.h"
#include "Func.h"
#include "ConvexNGon.h"

int main() {

	ConvexNGon shape(8, 100.f);
	sf::ConvexShape polygon = shape.createConvexNGon({ 400, 300 });

	// Проверка точек
	const auto& points = shape.getHullPoints();
	std::cout << "Hull points (" << points.size() << "):" << std::endl;
	for (const auto& p : points) {
		std::cout << "X: " << p.x << ", Y: " << p.y << std::endl;
	}

	int length = 800; //x
	int	width = 600; //y

	sf::RenderWindow window(sf::VideoMode(length, width), "Convex NGon");
	window.setFramerateLimit(60);

	srand(time(0));
	int side = rand() % (15 - 3 + 1) + 3;

	//// Задаем безопасные границы для центра фигуры
	float safePadding = 100.f; // Минимальное расстояние от краев экрана

	// Генерация радиусов (не больше safePadding)
	float radius_1 = 30.f + rand() % 70; // 30-100
	float radius_2 = 30.f + rand() % 70;

	// Координаты для правой фигуры (X ∈ [center + padding, right - padding])
	float X_right = (length / 2 + safePadding) + rand() % (length / 2 - 2 * static_cast<int>(safePadding)); //???
	float Y_right = safePadding + rand() % (width - 2 * static_cast<int>(safePadding));

	// Координаты для левой фигуры (X ∈ [padding, center - padding])
	float X_left = safePadding + rand() % (length / 2 - 2 * static_cast<int>(safePadding));
	float Y_left = safePadding + rand() % (width - 2 * static_cast<int>(safePadding));

	// Создание 1 фигуры слева
	ConvexNGon shape_1(side, radius_1);
	sf::ConvexShape shape_1_polygon = shape_1.createConvexNGon({ X_left,Y_left });
	shape_1_polygon.setFillColor(sf::Color::Cyan);
	shape_1_polygon.setOutlineThickness(-2.f);
	shape_1_polygon.setOutlineColor(sf::Color::Red);

	// Создание 1 фигуры справа
	ConvexNGon shape_2(side, radius_2);
	sf::ConvexShape shape_2_polygon = shape_2.createConvexNGon({ X_right,Y_right});
	shape_2_polygon.setFillColor(sf::Color::Green);
	shape_2_polygon.setOutlineThickness(2.f);
	shape_2_polygon.setOutlineColor(sf::Color::Yellow);

	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				window.close();
			if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::R) {


				float X_left = safePadding + rand() % (length / 2 - 2 * static_cast<int>(safePadding));
				float Y_left = safePadding + rand() % (width - 2 * static_cast<int>(safePadding));

				side = rand() % (15 - 3 + 1) + 3;
				float radius_1 = 30.f + rand() % 70;

				shape_1.change_SideAndRadius(side, radius_1);
				shape_1_polygon = shape_1.createConvexNGon({ X_left,Y_left });
				shape_1_polygon.setFillColor(sf::Color::Cyan);
				shape_1_polygon.setOutlineThickness(2.f);
				shape_1_polygon.setOutlineColor(sf::Color::Red);
			}

			if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::T) {

				float X_right = (length / 2 + safePadding) + rand() % (length / 2 - 2 * static_cast<int>(safePadding));
				float Y_right = safePadding + rand() % (width - 2 * static_cast<int>(safePadding));

				side = rand() % (15 - 3 + 1) + 3;
				float radius_1 = 30.f + rand() % 70;

				shape_2.change_SideAndRadius(side, radius_2);
				shape_2_polygon = shape_2.createConvexNGon({ X_right,Y_right });
				shape_2_polygon.setFillColor(sf::Color::Green);
				shape_2_polygon.setOutlineThickness(2.f);
				shape_2_polygon.setOutlineColor(sf::Color::Yellow);
			}
		}

		window.clear(sf::Color::Black);
		window.draw(shape_1_polygon);
		window.draw(shape_2_polygon);
		window.display();
	}

	return 0;
}