#pragma once

bool inRange(Box box) {
	if (eventInfo.mouseX >= box.x && eventInfo.mouseX <= box.x + box.w) {
		if (eventInfo.mouseY >= box.y && eventInfo.mouseY <= box.y + box.h) {
			return true;
		}
	}
	return false;
}

void drawWordSection() {
	//int cmon man
}

void drawGuessSection() {
	int x = 404;
	int y = 2;
	int w = WIDTH - 406;
	int h = HEIGHT - 4;
	drawSection(x, y, w, h, UI_WHITE, UI_BACKGROUND, 2);

	x += 2;
	y += 2;

	Box textBox = drawSection(x + 2, y + HEIGHT - 25, w - 8, 15);
	print(eventInfo.guess, textBox.x + 4, textBox.y + 4);
	print(to_str(eventInfo.guess.size()), textBox.x + textBox.w - 4, textBox.y + 4, UI_WHITE, 1, align::RIGHT);
}

void drawCanvasSection() {
	int x = 2;
	int y = 2;
	int w = 400;
	int h = HEIGHT - 4;
	drawSection(x, y, w, h, UI_WHITE, UI_BACKGROUND, 2);

	x += 2;
	y += 2;

	// Draw Tools
	for (int i = 0; i < 3; i++) {
		sf::Color color = UI_GREY;
		if (eventInfo.tool == i) {
			color = UI_WHITE;
		}
		drawSection(x + 2, y + 2 + i * 22, 20, 20, color);
		Box box = drawSprite(16 * i, 48, 16, 16, x + 4, y + 4 + i * 22);
		if (eventInfo.mouseUp) {
			if (inRange(box)) {
				eventInfo.tool = i;
			}
		}
	}
}

void drawUI() {
	drawGuessSection();
	drawCanvasSection();
	drawWordSection();

	print("X " + to_str(eventInfo.mouseX), 200, 100, UI_WHITE);
	print("Y " + to_str(eventInfo.mouseY), 200, 110, sf::Color::Green);
}

