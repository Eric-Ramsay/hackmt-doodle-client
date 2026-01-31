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

void fillShape(Point topLeft, Point topRight, Point botLeft, Point botRight, sf::Color color) {
	setPlainVertex(numVertices++, topLeft.x, topLeft.y, color); // 1
	setPlainVertex(numVertices++, topRight.x, topRight.y, color); // 2
	setPlainVertex(numVertices++, botLeft.x, botLeft.y, color); // 4
	setPlainVertex(numVertices++, botLeft.x, botLeft.y, color); // 4
	setPlainVertex(numVertices++, topRight.x, topRight.y, color); // 2
	setPlainVertex(numVertices++, botRight.x, botRight.y, color); //3
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

void drawLine(int x, int y, int width, sf::Color color) {

}