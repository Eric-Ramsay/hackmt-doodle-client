#pragma once

void setVertex(int index, int sX, int sY, int dX, int dY, sf::Color color) {
	sf::Vertex* vertex = &vertices[index];
	vertex->position.x = dX;
	vertex->position.y = dY;
	vertex->color = color;
	vertex->texCoords.x = sX;
	vertex->texCoords.y = sY;
}

void setPlainVertex(int index, int dX, int dY, sf::Color color) {
	sf::Vertex* vertex = &vertices[index];
	vertex->position.x = dX;
	vertex->position.y = dY;
	vertex->color = color;
	vertex->texCoords.x = 253;
	vertex->texCoords.y = 0;
}

void drawSprite(int sourceX, int sourceY, int width, int height, int drawX, int drawY, sf::Color color = sf::Color(255, 255, 255)) {
	setVertex(numVertices++, sourceX, sourceY, drawX, drawY, color); // 1
	setVertex(numVertices++, sourceX + width, sourceY, drawX + width, drawY, color); // 2
	setVertex(numVertices++, sourceX, sourceY + height, drawX, drawY + height, color); // 4
	setVertex(numVertices++, sourceX, sourceY + height, drawX, drawY + height, color); // 4
	setVertex(numVertices++, sourceX + width, sourceY, drawX + width, drawY, color); // 2
	setVertex(numVertices++, sourceX + width, sourceY + height, drawX + width, drawY + height, color); //3
}

void fillShape(Point topLeft, Point topRight, Point botLeft, Point botRight, sf::Color color) {
	setPlainVertex(numVertices++, topLeft.x, topLeft.y, color); // 1
	setPlainVertex(numVertices++, topRight.x, topRight.y, color); // 2
	setPlainVertex(numVertices++, botLeft.x, botLeft.y, color); // 4
	setPlainVertex(numVertices++, botLeft.x, botLeft.y, color); // 4
	setPlainVertex(numVertices++, topRight.x, topRight.y, color); // 2
	setPlainVertex(numVertices++, botRight.x, botRight.y, color); //3
}