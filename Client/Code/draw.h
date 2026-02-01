#pragma once

void setVertex(int index, int sX, int sY, int dX, int dY, sf::Color color) {
	if (index >= vertSize) {
		return;
	}
	sf::Vertex* vertex = &vertices[index];
	vertex->position.x = dX;
	vertex->position.y = dY;
	vertex->color = color;
	vertex->texCoords.x = sX;
	vertex->texCoords.y = sY;
}

void setPlainVertex(int index, int dX, int dY, sf::Color color) {
	if (index >= vertSize) {
		return;
	}
	sf::Vertex* vertex = &vertices[index];
	vertex->position.x = dX;
	vertex->position.y = dY;
	vertex->color = color;
	vertex->texCoords.x = 253;
	vertex->texCoords.y = 0;
}

void swap(Point& a, Point& b) {
	Point temp = a;
	a = b;
	b = temp;
}

void fillShape(Point topLeft, Point topRight, Point botLeft, Point botRight, sf::Color color) {
	Point tL = topLeft;
	Point tR = topRight;
	Point bL = botLeft;
	Point bR = botRight;
	if (tL.x > tR.x) {
		swap(tL, tR);
	}
	if (bL.x > bR.x) {
		swap(bL, bR);
	}
	if (tL.y > bL.y) {
		swap(tL, bL);
	}
	if (tR.y > bR.y) {
		swap(tR, bR);
	}

	setPlainVertex(numVertices++, tL.x, tL.y, color); // 1
	setPlainVertex(numVertices++, tR.x, tR.y, color); // 2
	setPlainVertex(numVertices++, bL.x, bL.y, color); // 4
	setPlainVertex(numVertices++, bL.x, bL.y, color); // 4
	setPlainVertex(numVertices++, tR.x, tR.y, color); // 2
	setPlainVertex(numVertices++, bR.x, bR.y, color); // 3
}

Box drawSprite(int sourceX, int sourceY, int width, int height, int drawX, int drawY, sf::Color color = sf::Color(255, 255, 255), int scaleX = 1, int scaleY = 1) {
	int w = width * scaleX;
	int h = height * scaleY;
	setVertex(numVertices++, sourceX, sourceY, drawX, drawY, color); // 1
	setVertex(numVertices++, sourceX + width, sourceY, drawX + w, drawY, color); // 2
	setVertex(numVertices++, sourceX, sourceY + height, drawX, drawY + h, color); // 4
	setVertex(numVertices++, sourceX, sourceY + height, drawX, drawY + h, color); // 4
	setVertex(numVertices++, sourceX + width, sourceY, drawX + w, drawY, color); // 2
	setVertex(numVertices++, sourceX + width, sourceY + height, drawX + w, drawY + h, color); //3

	return Box(drawX, drawY, w, h);
}

Box fillRect(int drawX, int drawY, int width, int height, sf::Color color) {
	return drawSprite(253, 0, 1, 1, drawX, drawY, color, width, height);
}

Box drawSection(int x, int y, int w, int h, sf::Color border = UI_WHITE, sf::Color inside = UI_BACKGROUND, int borderW = 1) {
	fillRect(x, y, w, h, border);
	fillRect(x + borderW, y + borderW, w - 2 * borderW, h - 2 * borderW, inside);
	return Box(x, y, w, h);
}

void drawLine(Point a, Point b, int width, sf::Color color) {
	Point vector(b.x - a.x, b.y - a.y);
	Point perpendicular(vector.y, -vector.x);

	int length = std::sqrt(perpendicular.x * perpendicular.x + perpendicular.y * perpendicular.y);
	Point normal(perpendicular.x / length, perpendicular.y / length);
	
	Point p1(a.x + normal.x * width / 2, a.y + normal.y * width / 2);
	Point p2(a.x - normal.x * width / 2, a.y - normal.y * width / 2);
	Point p3(b.x + normal.x * width / 2, b.y + normal.y * width / 2);
	Point p4(b.x - normal.x * width / 2, b.y - normal.y * width / 2);

	fillRect(p1.x, p1.y, 4, 4, sf::Color::Green);
	fillRect(p2.x, p2.y, 4, 4, sf::Color::Green);
	fillRect(p3.x, p3.y, 4, 4, sf::Color::Green);
	fillRect(p4.x, p4.y, 4, 4, sf::Color::Green);

	fillShape(p1, p2, p3, p4, color);
}