#include <SFML/Graphics.hpp>
#include <algorithm>
#include <ctime>
#include <iostream>
#include <cstdlib>
#include "Point.h"
#include "Func.h"
#include "ConvexNGon.h"

int main() {

	int length = 800; //x
	int	width = 600; //y

	sf::RenderWindow window(sf::VideoMode(length, width), "Convex NGon");
	window.setFramerateLimit(60);
	//// Задаем безопасные границы для центра фигуры
	float safePadding = 100.f; // Минимальное расстояние от краев экрана

	int side_1, side_2;
	float X_1, X_2, Y_1, Y_2, radius_1, radius_2;
	srand(time(0));

	side_1 = rand() % (15 - 3 + 1) + 3;
	side_2 = rand() % (15 - 3 + 1) + 3;

	// Генерация радиусов (не больше safePadding)
	radius_1 = 30.f + rand() % 70; // 30-100
	radius_2 = 30.f + rand() % 70;

	// Координаты для правой фигуры (X ∈ [center + padding, right - padding])
	X_1 = safePadding + rand() % (length - 2 * static_cast<int>(safePadding)); //???
	Y_1 = safePadding + rand() % (width - 2 * static_cast<int>(safePadding));

	// Координаты для левой фигуры (X ∈ [padding, center - padding])
	X_2 = safePadding + rand() % (length - 2 * static_cast<int>(safePadding));
	Y_2 = safePadding + rand() % (width - 2 * static_cast<int>(safePadding));

	//// Проверка, чтобы центры не пересекались:
	///*while (std::abs(X_right - X_left) < 2 * safePadding) {
	//	X_right = (length / 2 + safePadding) + rand() % (length / 2 - 2 * static_cast<int>(safePadding));
	//}*/

	// Создание 1 фигуры слева
	ConvexNGon shape_1(side_1, radius_1);
	sf::ConvexShape shape_1_polygon = shape_1.createConvexNGon({ X_1,Y_1 });
	/*shape_1_polygon.setFillColor(sf::Color::Cyan);
	shape_1_polygon.setOutlineThickness(-2.f);
	shape_1_polygon.setOutlineColor(sf::Color::Red);*/

	// Создание 1 фигуры справа
	ConvexNGon shape_2(side_2, radius_2);
	sf::ConvexShape shape_2_polygon = shape_2.createConvexNGon({ X_2,Y_2});
	/*shape_2_polygon.setFillColor(sf::Color::Green);
	shape_2_polygon.setOutlineThickness(2.f);
	shape_2_polygon.setOutlineColor(sf::Color::Yellow);*/

	//------------------------------------------------------------------------------------

	const auto& points_1 = shape_1.getHullPoints();
	std::vector<Point> points_1_absolute;
	for (const auto& p : points_1) {
		points_1_absolute.push_back({ X_1 + p.x, Y_1 + p.y });
	}

	const auto& points_2 = shape_2.getHullPoints();
	std::vector<Point> points_2_absolute;
	for (const auto& p : points_2) {
		points_2_absolute.push_back({ X_2 + p.x, Y_2 + p.y });
	}
	//--------------------------------------------------------------------------------------

	//получение абсолютных координат
	
	bool collision = SAT(points_1_absolute, points_2_absolute);
	
	while (!collision) {
		side_1 = rand() % (15 - 3 + 1) + 3;
		side_2 = rand() % (15 - 3 + 1) + 3;

		// Генерация радиусов (не больше safePadding)
		radius_1 = 30.f + rand() % 70; // 30-100
		radius_2 = 30.f + rand() % 70;

		X_1 = safePadding + rand() % (length - 2 * static_cast<int>(safePadding));
		Y_1 = safePadding + rand() % (width - 2 * static_cast<int>(safePadding));
		// Создание 1 фигуры слева
		ConvexNGon shape_1(side_1, radius_1);
		shape_1_polygon = shape_1.createConvexNGon({ X_1,Y_1 });

		X_2 = safePadding + rand() % (length - 2 * static_cast<int>(safePadding));
		Y_2 = safePadding + rand() % (width - 2 * static_cast<int>(safePadding));
		// Создание 1 фигуры справа
		ConvexNGon shape_2(side_2, radius_2);
		shape_2_polygon = shape_2.createConvexNGon({ X_2,Y_2 });

		////
		const auto& points_1 = shape_1.getHullPoints();
		std::vector<Point> points_1_absolute;
		for (const auto& p : points_1) {
			points_1_absolute.push_back({ X_1 + p.x, Y_1 + p.y });
		}
		
		const auto& points_2 = shape_2.getHullPoints();
		std::vector<Point> points_2_absolute;
		for (const auto& p : points_2) {
			points_2_absolute.push_back({ X_2 + p.x, Y_2 + p.y });
		}
	
		collision = SAT(points_1_absolute, points_2_absolute);

	}
	/*min_dist = SAT(points_1_absolute, points_2_absolute);
	std::cout <<"minimum distance between shapes: " << min_dist << std::endl;*/

	shape_1_polygon.setFillColor(sf::Color::Cyan);
	shape_1_polygon.setOutlineThickness(-2.f);
	shape_1_polygon.setOutlineColor(sf::Color::Red);

	shape_2_polygon.setFillColor(sf::Color::Green);
	shape_2_polygon.setOutlineThickness(-2.f);
	shape_2_polygon.setOutlineColor(sf::Color::Yellow);

	std::cout << "Hull points shape 1 (" << points_1_absolute.size() << "):" << std::endl;
	for (const auto& p : points_1_absolute) {
		std::cout << "X: " << p.x << ", Y: " << p.y << std::endl;
	}
	std::cout << "Hull points shape 2 (" << points_2_absolute.size() << "):" << std::endl;
	for (const auto& p : points_2_absolute) {
		std::cout << "X: " << p.x << ", Y: " << p.y << std::endl;
	}

	while (window.isOpen()) {

		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				window.close();

			if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::L) {
				//func
				const auto& points_1 = shape_1.getHullPoints();
				std::vector<Point> points_1_absolute;
				for (const auto& p : points_1) {
					points_1_absolute.push_back({ X_1 + p.x, Y_1 + p.y });
				}
				std::cout << "Hull points shape 1 (" << points_1_absolute.size() << "):" << std::endl;
				for (const auto& p : points_1_absolute) {
					std::cout << "X: " << p.x << ", Y: " << p.y << std::endl;
				}

				const auto& points_2 = shape_2.getHullPoints();
				std::vector<Point> points_2_absolute;
				for (const auto& p : points_2) {
					points_2_absolute.push_back({ X_2 + p.x, Y_2 + p.y });
				}

				collision = SAT(points_1_absolute, points_2_absolute);
				std::cout << "minimum distance between shapes: " << collision << std::endl;
			}

			if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::R) {

				points_1_absolute.clear();
				points_2_absolute.clear();

				X_1 = safePadding + rand() % (length - 2 * static_cast<int>(safePadding));
				Y_1 = safePadding + rand() % (width - 2 * static_cast<int>(safePadding));

				side_1 = rand() % (15 - 3 + 1) + 3;
				radius_1 = 30.f + rand() % 70;

				shape_1.change_SideAndRadius(side_1, radius_1);
				shape_1_polygon = shape_1.createConvexNGon({ X_1,Y_1 });

				const auto& points_1 = shape_1.getHullPoints();
				const auto& points_2 = shape_2.getHullPoints();

				for (const auto& p : points_1) {
					points_1_absolute.push_back({ X_1 + p.x, Y_1 + p.y });
				}
				for (const auto& p : points_2) {
					points_2_absolute.push_back({ X_2 + p.x, Y_2 + p.y });
				}

				collision = SAT(points_1_absolute, points_2_absolute);

				while (!collision) {
					X_1 = safePadding + rand() % (length - 2 * static_cast<int>(safePadding));
					Y_1 = safePadding + rand() % (width - 2 * static_cast<int>(safePadding));

					side_1 = rand() % (15 - 3 + 1) + 3;
					radius_1 = 30.f + rand() % 70;

					shape_1.change_SideAndRadius(side_1, radius_1);
					shape_1_polygon = shape_1.createConvexNGon({ X_1,Y_1 });

					const auto& points_1 = shape_1.getHullPoints();
					const auto& points_2 = shape_2.getHullPoints();

					for (const auto& p : points_1) {
						points_1_absolute.push_back({ X_1 + p.x, Y_1 + p.y });
					}
					for (const auto& p : points_2) {
						points_2_absolute.push_back({ X_2 + p.x, Y_2 + p.y });
					}

					collision = SAT(points_1_absolute, points_2_absolute);
				}

				shape_1_polygon.setFillColor(sf::Color::Cyan);
				shape_1_polygon.setOutlineThickness(-2.f);
				shape_1_polygon.setOutlineColor(sf::Color::Red);

				////////////////////////////////////////////////////////////////////////////////////
				system("cls");

				std::cout << "Hull points shape 1 (" << points_1.size() << "):" << std::endl;
				for (const auto& p : points_1) {
					std::cout << "X: " << p.x << ", Y: " << p.y << std::endl;
				}

				std::cout << "Hull points shape 2 (" << points_2.size() << "):" << std::endl;
				for (const auto& p : points_2) {
					std::cout << "X: " << p.x << ", Y: " << p.y << std::endl;
				}

			}

			if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::T) {

				points_1_absolute.clear();
				points_2_absolute.clear();

				X_2 = safePadding + rand() % (length - 2 * static_cast<int>(safePadding));
				Y_2 = safePadding + rand() % (width - 2 * static_cast<int>(safePadding));

				side_2 = rand() % (15 - 3 + 1) + 3;
				radius_2 = 30.f + rand() % 70;

				shape_2.change_SideAndRadius(side_2, radius_2);
				shape_2_polygon = shape_2.createConvexNGon({ X_2,Y_2 });

				const auto& points_1 = shape_1.getHullPoints();
				const auto& points_2 = shape_2.getHullPoints();

				for (const auto& p : points_1) {
					points_1_absolute.push_back({ X_1 + p.x, Y_1 + p.y });
				}
				for (const auto& p : points_2) {
					points_2_absolute.push_back({ X_2 + p.x, Y_2 + p.y });
				}

				collision = SAT(points_1_absolute, points_2_absolute);

				while (!collision) {
					X_2 = safePadding + rand() % (length - 2 * static_cast<int>(safePadding));
					Y_2 = safePadding + rand() % (width - 2 * static_cast<int>(safePadding));

					side_2 = rand() % (15 - 3 + 1) + 3;
					radius_2 = 30.f + rand() % 70;

					shape_2.change_SideAndRadius(side_2, radius_2);
					shape_2_polygon = shape_2.createConvexNGon({ X_2,Y_2 });

					const auto& points_1 = shape_1.getHullPoints();
					const auto& points_2 = shape_2.getHullPoints();

					for (const auto& p : points_1) {
						points_1_absolute.push_back({ X_1 + p.x, Y_1 + p.y });
					}
					for (const auto& p : points_2) {
						points_2_absolute.push_back({ X_2 + p.x, Y_2 + p.y });
					}

					collision = SAT(points_1_absolute, points_2_absolute);
				}

				shape_2_polygon.setFillColor(sf::Color::Green);
				shape_2_polygon.setOutlineThickness(-2.f);
				shape_2_polygon.setOutlineColor(sf::Color::Yellow);

				////////////////////////////////////////////////////////////////////////////////////
				system("cls");

				std::cout << "Hull points shape 1 (" << points_1.size() << "):" << std::endl;
				for (const auto& p : points_1) {
					std::cout << "X: " << p.x << ", Y: " << p.y << std::endl;
				}

				std::cout << "Hull points shape 2 (" << points_2.size() << "):" << std::endl;
				for (const auto& p : points_2) {
					std::cout << "X: " << p.x << ", Y: " << p.y << std::endl;
				}
			}
		}
		window.clear(sf::Color::Black);

		window.draw(shape_1_polygon);
		window.draw(shape_2_polygon);
		window.display();
	}
	return 0;
}