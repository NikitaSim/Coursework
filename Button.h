#pragma once

#include <SFML/Graphics.hpp>  // Для графических компонентов (RectangleShape, Text, Font)
#include <functional>         // Для std::function и лямбда-выражений
#include <string>             // Для работы со строками
#include <iostream>  

class Button {
private:
	sf::RectangleShape shape;
	sf::Text text;
	sf::Text minText;
	sf::Text maxText;
	sf::Font font;
	std::function<void()> action;
	bool isHovered;

public:
	Button(const sf::Vector2f& size, const sf::Vector2f& position, const std::string& label, const std::string& info = "")
		: isHovered(false) {

		if (!font.loadFromFile("C:/Users/niksi/source/repos/Coursework/Coursework/x64/Debug/Roboto_Condensed-Light.ttf")) {
			std::cerr << "Error loading font!" << std::endl;
		}

		shape.setSize(size);
		shape.setPosition(position);
		shape.setFillColor(sf::Color(200, 200, 200));
		shape.setOutlineThickness(2.f);
		shape.setOutlineColor(sf::Color::Black);

		text.setFont(font);
		text.setString(label);
		text.setCharacterSize(20);
		text.setFillColor(sf::Color::Black);
		text.setPosition(
			position.x + size.x / 2 - text.getGlobalBounds().width / 2,
			position.y + size.y / 2 - text.getGlobalBounds().height / 2
		);

		minText.setFont(font);
		minText.setString(info);
		minText.setCharacterSize(16);
		minText.setFillColor(sf::Color::Black);
		minText.setPosition(position.x, position.y + size.y + 5);

		maxText.setFont(font);
		maxText.setString(info);
		maxText.setCharacterSize(16);
		maxText.setFillColor(sf::Color::Black);
		maxText.setPosition(position.x, position.y + size.y + 25);
	}

	void setAction(std::function<void()> func) {
		action = func;
	}

	void update(const sf::Vector2i& mousePos) {
		isHovered = shape.getGlobalBounds().contains(mousePos.x, mousePos.y);
		shape.setFillColor(isHovered ? sf::Color(170, 170, 170) : sf::Color(200, 200, 200));
	}

	void click() const {
		if (isHovered && action) {
			action();
		}
	}

	void setMinInfo(const std::string& info) {
		minText.setString(info);
	}

	void setMaxInfo(const std::string& info) {
		maxText.setString(info);
	}

	void draw(sf::RenderWindow& window) const {
		window.draw(shape);
		window.draw(text);
		window.draw(minText);
		window.draw(maxText);
	}
};