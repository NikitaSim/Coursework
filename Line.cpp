#include <SFML/Graphics.hpp>
#include "Line.h"
#include "min_maxDistance.h"

sf::VertexArray Line::CreateLine() const {

	sf::VertexArray line(sf::Lines, 2);
	line[0].position = sf::Vector2f(vertex_start.x, vertex_start.y);
	line[1].position = sf::Vector2f(vertex_end.x, vertex_end.y);

	line[0].color = sf::Color::Red;
	line[1].color = sf::Color::Red;

	return line;
}

void Line::updateLine() {
    // Вычисляем длину и угол наклона
    float dx = vertex_end.x - vertex_start.x;
    float dy = vertex_end.y - vertex_start.y;
    float length = std::sqrt(dx * dx + dy * dy);
    float angle = std::atan2(dy, dx) * 180 / 3.14159f;

    // Настраиваем прямоугольник как линию
    lineShape.setSize(sf::Vector2f(length, 2.f)); // Толщина линии 2px
    lineShape.setPosition(vertex_start.x, vertex_start.y);
    lineShape.setRotation(angle);
    lineShape.setFillColor(sf::Color::Red);
}

sf::RectangleShape Line::getLine() const {
    return lineShape;
}