#pragma once


void charInfo(char c, int& sX, int& sY, int& sW, bool& drawChar) {
	sW = 5;
	if (c >= 'A' && c <= 'Z') {
		sX = 6 * (c - 'A');
		sY = 0;
	}
	if (c >= 'a' && c <= 'z') {
		sX = 6 * (c - 'a');
		sY = 16;
	}
	if (c >= '0' && c <= '9') {
		sX = 6 * (c - '0');
		sY = 32;
	}
	if (c == 'i' || c == 't' || c == 'l') {
		sW = 3;
	}
	if (c == 'j' || c == 'k' || c == 'f') {
		sW = 4;
	}
	if (c == ' ') {
		drawChar = false;
	}
}

int measureText(std::string text, float scale = 1) {
	int sX, sY, sW;
	int size = 0;
	bool printChar = true;
	for (char& c : text) {
		charInfo(c, sX, sY, sW, printChar);
		size += sW + 1;
	}
	return ((size - 1) * scale);
}


void print(std::string text, int x, int y, sf::Color color = UI_TEXT, int scale = 1, bool rightAlign = false) {
	int dX = x;
	int dY = y;
	if (rightAlign) {
		dX -= measureText(text);
	}
	for (char c : text) {
		bool drawChar = true;
		int sX = 0;
		int sY = 0;
		int sW = 6;

		charInfo(c, sX, sY, sW, drawChar);

		if (drawChar) {
			drawSprite(sX, sY, 5, 8, dX, dY, color, scale, scale);
		}
		dX += (sW + 1) * scale;
	}
}

void drawLine(Point a, Point b, int thickness, sf::Color color) {
	int width = b.x - a.x;
	int height = b.y - a.y;

	int len = std::sqrt(width * width + height * height);

	int xS = (thickness * height / len) / 2;
	int yS = (thickness * width / len) / 2;

	Point p1(a.x - xS, a.y + yS);
	Point p2(a.x + xS, a.y - yS);
	Point p3(b.x + xS, b.y - yS);
	Point p4(b.x - xS, b.y + yS);

	print(to_str(p1.x) + " " + to_str(p1.y) + " " + to_str(p2.x) + " " + to_str(p2.y) + " " + to_str(p3.x) + " " + to_str(p3.y) + " " + to_str(p4.x) + " " + to_str(p4.y), 200, 200);
	fillRect(p1.x, p1.y, 4, 4, sf::Color::Green);
	fillRect(p2.x, p2.y, 4, 4, sf::Color::Green);
	fillRect(p3.x, p3.y, 4, 4, sf::Color::Green);
	fillRect(p4.x, p4.y, 4, 4, sf::Color::Green);

	fillShape(p2, p1, p3, p4, color);
}