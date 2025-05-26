#pragma once

#include <SFML/Graphics.hpp>
#include <string>

class Text {
private:
	sf::Font font;
	std::string content;
	int size;
public:

	Text(sf::Font font, std::string str, int size) :
		font(font), content(str), size(size){}

	sf::Text getText();
};