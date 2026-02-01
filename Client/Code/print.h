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
