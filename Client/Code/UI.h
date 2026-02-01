#pragma once

bool inRange(Box box) {
	if (eventInfo.mouseX >= box.x && eventInfo.mouseX <= box.x + box.w) {
		if (eventInfo.mouseY >= box.y && eventInfo.mouseY <= box.y + box.h) {
			return true;
		}
	}
	return false;
}

void drawOnCanvas() {
	// Draw on the canvas
	if (inRange(Box(CANVAS_X, CANVAS_Y, CANVAS_W, CANVAS_H))) {
		if (eventInfo.mouseDown && eventInfo.tool != BUCKET) {
			std::string color = eventInfo.color;
			if (eventInfo.tool == ERASER) {
				color = eventInfo.backgroundColor;
			}
			if (newDraw) {
				newDraw = false;
				actions.push_back(Action(Point(eventInfo.mouseX, eventInfo.mouseY), Point(), eventInfo.cursorSize, eventInfo.tool, color));
				return;
			}
			Line* last = &actions[actions.size() - 1].line;
			if (std::abs(last->a.x - eventInfo.mouseX) >= eventInfo.cursorSize || std::abs(last->a.y - eventInfo.mouseY) >= eventInfo.cursorSize) {
				last->b = Point(eventInfo.mouseX, eventInfo.mouseY);

				if (actions.size() > 25) {
					// Send actions to the server

					// Set actions to empty
				}

				actions.push_back(Action(Point(eventInfo.mouseX, eventInfo.mouseY), Point(), eventInfo.cursorSize, eventInfo.tool, color));
			}
		}
		else if (eventInfo.mouseUp && eventInfo.tool == BUCKET) {
			actions.push_back(Action(Point(eventInfo.mouseX, eventInfo.mouseY), Point(), eventInfo.cursorSize, eventInfo.tool, eventInfo.color));
		}
	}
	else {
		if (actions.size() > 0 && (actions[actions.size() - 1].tool != BUCKET && actions[actions.size() - 1].line.b.x == 0 && actions[actions.size() - 1].line.b.y == 0)) {
			actions.pop_back();
		}
	}
}

void drawWordSection() {
	int x = 408;
	int y = 6;
	int w = WIDTH - 414;
	int h = 100;
	drawSection(x, y, w, h);
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
	print(to_str(eventInfo.guess.size()), textBox.x + textBox.w - 4, textBox.y + 4, UI_WHITE, 1, true);
}

void drawCanvasSection() {
	bool buttonClicked = false;
	int x = CANVAS_X + 2;
	int y = CANVAS_Y + 2;
	drawSection(CANVAS_X, CANVAS_Y, CANVAS_W, CANVAS_H, UI_WHITE, getColor(eventInfo.backgroundColor), 2);


	std::vector<std::string> colors = {"black", "red", "green", "blue", "yellow", "orange", "pink", "brown"};
	for (int i = 0; i < colors.size(); i++) {
		Box box = drawSection(x + 2 + i * 20, y + HEIGHT - 28, 18, 18, UI_WHITE, UI_WHITE);
		fillRect(x + 3 + i * 20, y + HEIGHT - 27, 16, 16, getColor(colors[i]));
		if (eventInfo.mouseUp && inRange(box)) {
			eventInfo.color = colors[i];
			buttonClicked = true;
		}
	}

	// Draw Tools
	for (int i = 0; i < 3; i++) {
		sf::Color color = UI_GREY;
		if (eventInfo.tool == i) {
			color = UI_WHITE;
		}
		drawSection(x + 2, y + 2 + i * 22, 20, 20, color, getColor(eventInfo.backgroundColor));
		Box box = drawSprite(16 * i, 48, 16, 16, x + 4, y + 4 + i * 22);
		if (eventInfo.mouseUp) {
			if (inRange(box)) {
				eventInfo.tool = (TOOL)i;
				buttonClicked = true;
			}
		}
	}

	drawSection(x + 2, y + 2 + 3 * 22, 20, 20, UI_WHITE, UI_WHITE);
	fillRect(x + 3, y + 3 + 3 * 22, 18, 18, getColor(eventInfo.color));

	int size = actions.size();

	if (!buttonClicked) {
		drawOnCanvas();
	}

	for (int i = actions.size() - 1; i >= 0; i--){
		if (actions[i].tool == BUCKET) {
			eventInfo.backgroundColor = actions[i].color;
		}
		else if (i == actions.size() - 1 && (actions[i].line.b.x == 0 || actions[i].line.b.y == 0))
		{
			continue;
		}
		

		if (actions[i].tool == PENCIL || actions[i].tool == ERASER) {
			drawLine(actions[i].line.a, actions[i].line.b, actions[i].width, getColor(actions[i].color));
		}

		drawCursor(actions[i].line.a, actions[i].width - 1, getColor(actions[i].color));
		drawCursor(actions[i].line.b, actions[i].width - 1, getColor(actions[i].color));
	}
}

void drawUI() {
	drawGuessSection();
	drawCanvasSection();
	drawWordSection();

	print("X " + to_str(eventInfo.mouseX), 200, 100, UI_WHITE);
	print("Y " + to_str(eventInfo.mouseY), 200, 110, sf::Color::Green);
}

