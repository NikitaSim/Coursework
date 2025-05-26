#include <SFML/Graphics.hpp>
#include "text.h"

sf::Text Text::getText() {

	sf::Text text;

	text.setFont(font);
	text.setString(content);
	text.setCharacterSize(size);
	//text.setFillColor(color);

	return text;
}