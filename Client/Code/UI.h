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
	if (eventInfo.mouseDown && inRange(Box(CANVAS_X, CANVAS_Y, CANVAS_W, CANVAS_H))) {
		Line* last = &actions[actions.size() - 1].line;
		if (std::abs(last->a.x - eventInfo.mouseX) >= 5 || std::abs(last->a.y - eventInfo.mouseY) >= 5) {
			last->b = Point(eventInfo.mouseX, eventInfo.mouseY);

			if (actions.size() > 25) {
				// Send actions to the server
				nlohmann::json actionsJson;
				actionsJson["actions"] = actions;

				httplib::Client cli("http://localhost:5062");
				auto drawRequest = cli.Post("/players/send-drawing-data/", actionsJson.dump(), "application/json");

				actions = {};
				// Set actions to empty
			}

			actions.push_back(Action(Point(eventInfo.mouseX, eventInfo.mouseY), Point(), 6, PENCIL, "green"));
		}
	}
}

void drawWordSection() {

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
	int x = CANVAS_X + 2;
	int y = CANVAS_Y + 2;
	drawSection(CANVAS_X, CANVAS_Y, CANVAS_W, CANVAS_H, UI_WHITE, UI_BACKGROUND, 2);

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
	int size = actions.size();

	drawOnCanvas();

	for (int i = 0; i < size; i++){
		if (i + 1 == size && (actions[i].line.b.x == 0 || actions[i].line.b.y == 0))
		{
			break;
		}

		drawLine(actions[i].line.a, actions[i].line.b, actions[i].width, sf::Color::Green);
	}
}

void drawUI() {
	drawGuessSection();
	drawCanvasSection();
	drawWordSection();

	print("X " + to_str(eventInfo.mouseX), 200, 100, UI_WHITE);
	print("Y " + to_str(eventInfo.mouseY), 200, 110, sf::Color::Green);
}

