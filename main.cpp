#include <SFML/Graphics.hpp>
//#include <algorithm>
#include <ctime>
#include "Point.h"
#include "Func.h"
#include "ConvexNGon.h"

int main() {

	int length = 800; //x
	int	width = 600; //y

	sf::RenderWindow window(sf::VideoMode(length, width), "Convex NGon");
	window.setFramerateLimit(60);

	srand(time(0));
	int side = rand() % (15 - 3 + 1) + 3;
	float radius = 50.f + (rand() % 50);

	// Задаем безопасные границы для центра фигуры
	float safePadding = 100.f; // Минимальное расстояние от краев экрана

	// Генерация координат центра с учетом радиуса
	float X_rand = rand() % ((length / 2) - 2 * static_cast<int>(safePadding)) + safePadding;
	float Y_rand = rand() % (width - 2 * static_cast<int>(safePadding)) + safePadding;

	//sf::ConvexShape shape_1 = createConvexNGon(side, 100.f, { 250, 300 });
	ConvexNGon shape_1(side, radius);
	sf::ConvexShape shape_1_polygon = shape_1.createConvexNGon({ X_rand,Y_rand });
	shape_1_polygon.setFillColor(sf::Color::Cyan);
	shape_1_polygon.setOutlineThickness(-2.f);
	shape_1_polygon.setOutlineColor(sf::Color::Red);

	//sf::ConvexShape shape_2 = createConvexNGon(side, 100.f, { 550, 300 });
	ConvexNGon shape_2(side, 100.f);
	sf::ConvexShape shape_2_polygon = shape_2.createConvexNGon({ 550,300 });
	shape_2_polygon.setFillColor(sf::Color::Green);
	shape_2_polygon.setOutlineThickness(2.f);
	shape_2_polygon.setOutlineColor(sf::Color::Yellow);

	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				window.close();
			if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::R) {

				X_rand = rand() % ((length / 2) - 100 + 1) + 100;
				Y_rand = rand() % ((width - 50) - 100 + 1) + 100;
				side = rand() % (15 - 3 + 1) + 3;

				shape_1.change_side(side);
				shape_1_polygon = shape_1.createConvexNGon({ X_rand,Y_rand });
				shape_1_polygon.setFillColor(sf::Color::Cyan);
				shape_1_polygon.setOutlineThickness(2.f);
				shape_1_polygon.setOutlineColor(sf::Color::Red);
			}

			if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::T) {
				side = rand() % (15 - 3 + 1) + 3;
				shape_2.change_side(side);
				shape_2_polygon = shape_2.createConvexNGon({ 550,300 });
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