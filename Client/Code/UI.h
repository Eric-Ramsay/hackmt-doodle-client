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
			if (std::abs(last->a.x - eventInfo.mouseX) >= eventInfo.cursorSize || std::abs(last->a.y - eventInfo.mouseY) >= eventInfo.cursorSize/2) {
				last->b = Point(eventInfo.mouseX, eventInfo.mouseY);

				if (actions.size() > 10) {
					// Send actions to the server
					nlohmann::json actionsJson;
					actionsJson["actions"] = actions;

					httplib::Client cli("http://localhost:5062");
					//auto drawRequest = cli.Post("/players/send-drawing-data/", actionsJson.dump(), "application/json");

					actions = {};
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

void drawCanvas(std::vector<Action> actionlist) {
	for (int i = actionlist.size() - 1; i >= 0; i--) {
		if (actionlist[i].tool == BUCKET) {
			eventInfo.backgroundColor = actionlist[i].color;
		}
		else if (i == actionlist.size() - 1 && (actionlist[i].line.b.x == 0 || actionlist[i].line.b.y == 0))
		{
			drawCursor(actionlist[i].line.a, actionlist[i].width - 1, getColor(actionlist[i].color));
			continue;
		}

		if (actionlist[i].tool == PENCIL || actionlist[i].tool == ERASER) {
			drawLine(actionlist[i].line.a, actionlist[i].line.b, actionlist[i].width, getColor(actionlist[i].color));
			drawCursor(actionlist[i].line.a, actionlist[i].width - 1, getColor(actionlist[i].color));
			drawCursor(actionlist[i].line.b, actionlist[i].width - 1, getColor(actionlist[i].color));
		}
	}
}


void drawWordSection() {
	int x = 408;
	int y = 6;
	int w = WIDTH - 414;
	int h = 100;
	drawSection(x, y, w, h);
	print(gameState.currentWord, x + w / 2, y + 12, UI_TEXT, 1, CENTER);
	int len = measureText(gameState.currentWord, 1);

	print(to_str(gameState.timeRemaining), x + w - 4, y + h - 10, UI_TEXT, 1, RIGHT);
	print("Round " + to_str(gameState.round), x + 4, y + h - 10);
	print("Score " + to_str(gameState.score), x + WIDTH / 2, y + h - 10);
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
	print(to_str(eventInfo.guess.size()), textBox.x + textBox.w - 4, textBox.y + 4, UI_WHITE, 1, RIGHT);


	int numGuesses = min(gameState.messages.size(), 15);
	for (int i = 0; i < numGuesses; i++) {
		if (gameState.messages[i].succes) {
			print(to_str(gameState.messages[i].id) + " guessed the word", x + w/2, y + HEIGHT - (35 + i * 15), getColor("green"), 1, CENTER);
		}
		else {
			print(to_str(gameState.messages[i].id), x + 2, y + HEIGHT - (35 + i * 15));
		}
	}
}

void drawCanvasSection() {
	bool buttonClicked = false;
	int x = CANVAS_X + 2;
	int y = CANVAS_Y + 2;
	drawSection(CANVAS_X, CANVAS_Y, CANVAS_W, CANVAS_H, UI_WHITE, getColor(eventInfo.backgroundColor), 2);

	if (gameState.drawingId == gameState.id) {
		std::vector<std::string> colors = { "black", "red", "green", "blue", "yellow", "orange", "pink", "brown" };
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
		drawCursor(Point(eventInfo.mouseX, eventInfo.mouseY), eventInfo.cursorSize, getColor(eventInfo.color));
	}

	drawSection(x + 2, y + 2 + 3 * 22, 20, 20, UI_WHITE, UI_WHITE);
	fillRect(x + 3, y + 3 + 3 * 22, 18, 18, getColor(eventInfo.color));

	int size = actions.size();

	if (!buttonClicked) {
		drawOnCanvas();
	}

	drawCanvas(actions);
	drawCanvas(gameState.actions);
}

void drawWordOptions() {
	print("Pick a word to draw", WIDTH / 2, 30, UI_TEXT, 1, CENTER);

	for (int i = 0; i < gameState.wordOptions.size(); i++) {
		Box box = drawSection(WIDTH / 2 - 100, 50 + 80 * i, 200, 20);
		print(gameState.wordOptions[i], WIDTH / 2, box.y + 4);
		if (inRange(box)) {
			// Post word choice
			nlohmann::json wordChoiceRequest;
			wordChoiceRequest["clientId"] = "test";
			wordChoiceRequest["word"] = gameState.wordOptions[i];
			httplib::Client cli("http://localhost:5062");
			auto drawRequest = cli.Post("/state/word/", wordChoiceRequest.dump(), "application/json");

			drawing = DRAW_UI;
			gameState.wordOptions = {};
		}
	}
}

void drawEnterName() {
	print("Please Enter your Name", WIDTH / 2, 150, UI_TEXT, 1, CENTER);

	Box box = drawSection(WIDTH / 2 - 100, 170, 200, 20);
	print(eventInfo.guess, WIDTH / 2, box.y + 6, UI_TEXT, 1, CENTER);
}

void drawUI() {

	if (drawing == DRAW_UI) {
		drawGuessSection();
		drawCanvasSection();
		drawWordSection();
	}
	else if (drawing == ENTER_NAME) {
		drawEnterName();
	}
	else if (drawing == PICK_WORD) {
		drawWordOptions();
	}
}

