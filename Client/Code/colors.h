#pragma once

sf::Color UI_BACKGROUND(90, 90, 190);
sf::Color UI_TEXT(20, 20, 20);
sf::Color UI_WHITE(240, 240, 230);
sf::Color UI_GREY(120, 120, 110);

sf::Color getColor(std::string color) {
	if (color == "white") {
		return sf::Color::White;
	}
	if (color == "black") {
		return sf::Color::Black;
	}
	if (color == "red") {
		return sf::Color::Red;
	}
	if (color == "green") {
		return sf::Color::Green;
	}
	if (color == "blue") {
		return UI_BACKGROUND;
	}
	if (color == "yellow") {
		return sf::Color::Yellow;
	}
	if (color == "orange") {
		return sf::Color(240, 130, 0);
	}
	if (color == "brown") {
		return sf::Color(160, 80, 45);
	}
	return sf::Color::Magenta;
}
