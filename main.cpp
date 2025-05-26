#include <SFML/Graphics.hpp>
#include <algorithm>
#include <ctime>
#include <iostream>
#include <cstdlib>
#include "Point.h"
#include "Func.h"
#include "ConvexNGon.h"
#include "min_maxDistance.h"
#include "Line.h"
#include "text.h"
#include "Button.h"

int main() {

	int length = 800; //x
	int	width = 600; //y

	std::string text = "100px";

	sf::VertexArray line_min(sf::Lines, 2);
	sf::VertexArray line_max(sf::Lines, 2);

	bool show_min_line = false;
	bool show_max_line = false;

	sf::VertexArray line_scale(sf::Lines, 2);
	sf::RectangleShape lineShape;

	Line scale({ 20,580}, { 120,580 });
	line_scale = scale.CreateLine();

	Line rectangle({ 150,450 }, { 150,550 });
	rectangle.updateLine();
	lineShape = rectangle.getLine();

	sf::Text scale_mes;

	sf::Font font;
	if (!font.loadFromFile("arial.ttf")) {
		std::cerr << "Error loading font!" << std::endl;
		return EXIT_FAILURE;
	}

	Text text_mes(font, text, 15);
	scale_mes = text_mes.getText();
	scale_mes.setFillColor(sf::Color::Red);
	scale_mes.setPosition({ 20,550 });

	sf::RenderWindow window(sf::VideoMode(length, width), "Convex NGon");
	window.setFramerateLimit(60);

	sf::RenderWindow instrument_menu(sf::VideoMode(300, 400), "Menu");
	instrument_menu.setFramerateLimit(60);

	//// Задаем безопасные границы для центра фигуры
	float safePadding = 100.f; // Минимальное расстояние от краев экрана

	int side_1, side_2;
	float X_1, X_2, Y_1, Y_2, radius_1, radius_2;
	srand(time(0));

	//----------------------------------------------------------------------------------------//

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

	// Создание 1 фигуры слева
	ConvexNGon shape_1(side_1, radius_1);
	sf::ConvexShape shape_1_polygon = shape_1.createConvexNGon({ X_1,Y_1 });

	// Создание 1 фигуры справа
	ConvexNGon shape_2(side_2, radius_2);
	sf::ConvexShape shape_2_polygon = shape_2.createConvexNGon({ X_2,Y_2});
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
	
	while (collision) {

		points_1_absolute.clear();
		points_2_absolute.clear();

		side_1 = rand() % (15 - 3 + 1) + 3;
		side_2 = rand() % (15 - 3 + 1) + 3;

		// Генерация радиусов (не больше safePadding)
		radius_1 = 30.f + rand() % 70; // 30-100
		radius_2 = 30.f + rand() % 70;

		X_1 = safePadding + rand() % (length - 2 * static_cast<int>(safePadding));
		Y_1 = safePadding + rand() % (width - 2 * static_cast<int>(safePadding));
		// Создание 1 фигуры слева
		shape_1.change_SideAndRadius(side_1, radius_1);
		shape_1_polygon = shape_1.createConvexNGon({ X_1,Y_1 });

		X_2 = safePadding + rand() % (length - 2 * static_cast<int>(safePadding));
		Y_2 = safePadding + rand() % (width - 2 * static_cast<int>(safePadding));
		// Создание 1 фигуры справа
		shape_2.change_SideAndRadius(side_2, radius_2);
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

	shape_1_polygon.setFillColor(sf::Color::Cyan); // этот блок в отдельную функцию(метод)
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

	// КНОПКИ

	float MinDistance = 0.f;
	float MaxDistance = 0.f;
	// Создаем кнопки в меню

	Button btnD(sf::Vector2f(120, 40), sf::Vector2f(20, 20), "Show Distance", "Distance: ");
	Button btnR(sf::Vector2f(120, 40), sf::Vector2f(20, 120), "Reset Left");
	Button btnT(sf::Vector2f(120, 40), sf::Vector2f(20, 180), "Reset Right");

	// Настройка действий для кнопок
	btnD.setAction([&]() {
		Distance min_distance = minDistance(points_1_absolute, points_2_absolute);
		Distance max_distance = maxDistance(points_1_absolute, points_2_absolute);

		Line min_line(min_distance.start_point, min_distance.end_point);
		Line max_line(max_distance.start_point, max_distance.end_point);

		line_min = min_line.CreateLine();
		line_max = max_line.CreateLine();

		MinDistance = min_distance.length;
		MaxDistance = max_distance.length;

		btnD.setMinInfo("Min distance: " + std::to_string(MinDistance));
		btnD.setMaxInfo("Max distance: " + std::to_string(MaxDistance));

		show_min_line = true;
		show_max_line = true;
		});

	btnR.setAction([&]() {
		// Код обновления левой фигуры (как для клавиши R)
		// ...
		points_1_absolute.clear();

		X_1 = safePadding + rand() % (length - 2 * static_cast<int>(safePadding));
		Y_1 = safePadding + rand() % (width - 2 * static_cast<int>(safePadding));

		side_1 = rand() % (15 - 3 + 1) + 3;
		radius_1 = 30.f + rand() % 70;

		shape_1.change_SideAndRadius(side_1, radius_1);
		shape_1_polygon = shape_1.createConvexNGon({ X_1,Y_1 });

		const auto& points_1 = shape_1.getHullPoints();

		for (const auto& p : points_1) {
			points_1_absolute.push_back({ X_1 + p.x, Y_1 + p.y });
		}

		collision = SAT(points_1_absolute, points_2_absolute);

		while (collision) {

			points_1_absolute.clear();

			X_1 = safePadding + rand() % (length - 2 * static_cast<int>(safePadding));
			Y_1 = safePadding + rand() % (width - 2 * static_cast<int>(safePadding));

			side_1 = rand() % (15 - 3 + 1) + 3;
			radius_1 = 30.f + rand() % 70;

			shape_1.change_SideAndRadius(side_1, radius_1);
			shape_1_polygon = shape_1.createConvexNGon({ X_1,Y_1 });

			const auto& points_1 = shape_1.getHullPoints();

			for (const auto& p : points_1) {
				points_1_absolute.push_back({ X_1 + p.x, Y_1 + p.y });
			}

			collision = SAT(points_1_absolute, points_2_absolute);
		}

		shape_1_polygon.setFillColor(sf::Color::Cyan);
		shape_1_polygon.setOutlineThickness(-2.f);
		shape_1_polygon.setOutlineColor(sf::Color::Red);

		show_min_line = false;
		show_max_line = false;

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

		show_min_line = false;
		show_max_line = false;
		//btnD.setInfo("Distance: ");
		});

	btnT.setAction([&]() {
		// Код обновления правой фигуры (как для клавиши T)
		// ...
		points_2_absolute.clear();

		X_2 = safePadding + rand() % (length - 2 * static_cast<int>(safePadding));
		Y_2 = safePadding + rand() % (width - 2 * static_cast<int>(safePadding));

		side_2 = rand() % (15 - 3 + 1) + 3;
		radius_2 = 30.f + rand() % 70;

		shape_2.change_SideAndRadius(side_2, radius_2);
		shape_2_polygon = shape_2.createConvexNGon({ X_2,Y_2 });

		const auto& points_2 = shape_2.getHullPoints();

		for (const auto& p : points_2) {
			points_2_absolute.push_back({ X_2 + p.x, Y_2 + p.y });
		}

		collision = SAT(points_1_absolute, points_2_absolute);

		while (collision) {

			points_2_absolute.clear();

			X_2 = safePadding + rand() % (length - 2 * static_cast<int>(safePadding));
			Y_2 = safePadding + rand() % (width - 2 * static_cast<int>(safePadding));

			side_2 = rand() % (15 - 3 + 1) + 3;
			radius_2 = 30.f + rand() % 70;

			shape_2.change_SideAndRadius(side_2, radius_2);
			shape_2_polygon = shape_2.createConvexNGon({ X_2,Y_2 });

			const auto& points_2 = shape_2.getHullPoints();

			for (const auto& p : points_2) {
				points_2_absolute.push_back({ X_2 + p.x, Y_2 + p.y });
			}

			collision = SAT(points_1_absolute, points_2_absolute);
		}

		shape_2_polygon.setFillColor(sf::Color::Green);
		shape_2_polygon.setOutlineThickness(-2.f);
		shape_2_polygon.setOutlineColor(sf::Color::Yellow);

		show_min_line = false;
		show_max_line = false;

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

		show_min_line = false;
		show_max_line = false;
		//bbtnD.setInfo("Distance: ");
		});

	while (window.isOpen() && instrument_menu.isOpen()) {

		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				window.close();
			if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::D) {

				show_min_line = true;
				show_max_line = true;

				Distance min_distance = minDistance(points_1_absolute, points_2_absolute);
				std::cout << "min distance between: " << min_distance.length << std::endl;
				
				Line line(min_distance.start_point, min_distance.end_point);
				line_min = line.CreateLine();
				//lineShape = line.getLine();

				Distance max_Distance = maxDistance(points_1_absolute, points_2_absolute);
				std::cout << "max distance between: " << max_Distance.length << std::endl;

				Line max_line(max_Distance.start_point, max_Distance.end_point);
				line_max = max_line.CreateLine();
				//min_maxDistance
			}

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

				X_1 = safePadding + rand() % (length - 2 * static_cast<int>(safePadding));
				Y_1 = safePadding + rand() % (width - 2 * static_cast<int>(safePadding));

				side_1 = rand() % (15 - 3 + 1) + 3;
				radius_1 = 30.f + rand() % 70;

				shape_1.change_SideAndRadius(side_1, radius_1);
				shape_1_polygon = shape_1.createConvexNGon({ X_1,Y_1 });

				const auto& points_1 = shape_1.getHullPoints();

				for (const auto& p : points_1) {
					points_1_absolute.push_back({ X_1 + p.x, Y_1 + p.y });
				}

				collision = SAT(points_1_absolute, points_2_absolute);

				while (collision) {

					points_1_absolute.clear();

					X_1 = safePadding + rand() % (length - 2 * static_cast<int>(safePadding));
					Y_1 = safePadding + rand() % (width - 2 * static_cast<int>(safePadding));

					side_1 = rand() % (15 - 3 + 1) + 3;
					radius_1 = 30.f + rand() % 70;

					shape_1.change_SideAndRadius(side_1, radius_1);
					shape_1_polygon = shape_1.createConvexNGon({ X_1,Y_1 });

					const auto& points_1 = shape_1.getHullPoints();

					for (const auto& p : points_1) {
						points_1_absolute.push_back({ X_1 + p.x, Y_1 + p.y });
					}

					collision = SAT(points_1_absolute, points_2_absolute);
				}

				shape_1_polygon.setFillColor(sf::Color::Cyan);
				shape_1_polygon.setOutlineThickness(-2.f);
				shape_1_polygon.setOutlineColor(sf::Color::Red);

				show_min_line = false;
				show_max_line = false;

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

				points_2_absolute.clear();

				X_2 = safePadding + rand() % (length - 2 * static_cast<int>(safePadding));
				Y_2 = safePadding + rand() % (width - 2 * static_cast<int>(safePadding));

				side_2 = rand() % (15 - 3 + 1) + 3;
				radius_2 = 30.f + rand() % 70;

				shape_2.change_SideAndRadius(side_2, radius_2);
				shape_2_polygon = shape_2.createConvexNGon({ X_2,Y_2 });

				const auto& points_2 = shape_2.getHullPoints();

				for (const auto& p : points_2) {
					points_2_absolute.push_back({ X_2 + p.x, Y_2 + p.y });
				}

				collision = SAT(points_1_absolute, points_2_absolute);

				while (collision) {

					points_2_absolute.clear();

					X_2 = safePadding + rand() % (length - 2 * static_cast<int>(safePadding));
					Y_2 = safePadding + rand() % (width - 2 * static_cast<int>(safePadding));

					side_2 = rand() % (15 - 3 + 1) + 3;
					radius_2 = 30.f + rand() % 70;

					shape_2.change_SideAndRadius(side_2, radius_2);
					shape_2_polygon = shape_2.createConvexNGon({ X_2,Y_2 });

					const auto& points_2 = shape_2.getHullPoints();

					for (const auto& p : points_2) {
						points_2_absolute.push_back({ X_2 + p.x, Y_2 + p.y });
					}

					collision = SAT(points_1_absolute, points_2_absolute);
				}

				shape_2_polygon.setFillColor(sf::Color::Green);
				shape_2_polygon.setOutlineThickness(-2.f);
				shape_2_polygon.setOutlineColor(sf::Color::Yellow);

				show_min_line = false;
				show_max_line = false;

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

		sf::Vector2i mousePos = sf::Mouse::getPosition(instrument_menu);
		while (instrument_menu.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				instrument_menu.close();
			}
			if (event.type == sf::Event::MouseButtonPressed) {
				if (event.mouseButton.button == sf::Mouse::Left) {
					btnD.click();
					btnR.click();
					btnT.click();
				}
			}
		}

		// Обновление кнопок
		btnD.update(mousePos);
		btnR.update(mousePos);
		btnT.update(mousePos);

		instrument_menu.clear(sf::Color::White);
		window.clear(sf::Color::Black);

		window.draw(shape_1_polygon);
		window.draw(shape_2_polygon);

		window.draw(line_scale);

		if (show_min_line) window.draw(line_min);
		if (show_max_line) window.draw(line_max);

		//window.draw(lineShape);

		window.draw(scale_mes);

		// Отрисовка меню
		btnD.draw(instrument_menu);
		btnR.draw(instrument_menu);
		btnT.draw(instrument_menu);
		
		window.display();
		instrument_menu.display();
	}
	return 0;
}