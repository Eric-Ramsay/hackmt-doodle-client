#pragma once

void checkDraw(bool newDraw)
{
	Action newAction;
	int size = actions.size() - 1;
	int prevX = 0;
	int prevY = 0;

	if (actions.size() != 0)
	{
		prevX = actions[size].line.b.x;
		prevY = actions[size].line.b.y;
	}

	if (eventInfo.mouseDown == true &&
		eventInfo.mouseX > CANVAS_X && 
			eventInfo.mouseX < CANVAS_W && 
			eventInfo.mouseY > CANVAS_Y && 
			eventInfo.mouseY < CANVAS_H) {
		//points.push_back(Point(eventInfo.mouseX, eventInfo.mouseY));
		if (newDraw || (prevX != 0 && prevY != 0))
		{
			if (newDraw && actions.size() != 0 && (actions[size].line.b.x == 0 || actions[size].line.b.y == 0) ) {
				actions.pop_back();
			}
			newAction.line.a.x = eventInfo.mouseX;
			newAction.line.a.y = eventInfo.mouseY;
			newAction.width = 12;
			newAction.color = "Green";
			actions.push_back(newAction);
		}
		else if ( prevX < eventInfo.mouseX - 5 || 
			 	  prevX > eventInfo.mouseX + 5 || 
				  prevY < eventInfo.mouseY - 5 || 
				  prevY > eventInfo.mouseY + 5 ) {
			actions[size].line.b.x = eventInfo.mouseX;
			actions[size].line.b.y = eventInfo.mouseY;
		}
	}
}

bool inRange(Box box) {
	if (eventInfo.mouseX >= box.x && eventInfo.mouseX <= box.x + box.w) {
		if (eventInfo.mouseY >= box.y && eventInfo.mouseY <= box.y + box.h) {
			return true;
		}
	}
	return false;
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
	checkDraw(false);
	int size = actions.size();
	for(int i = 0; i < size; i++){
		if (size == 0 )
		{
			break;
		}
		else if (i+1 == size && (actions[i].line.b.x == 0 || actions[i].line.b.y == 0))
		{
			break;
		}

		//std::cout << i << " " << actions[i].line.a.x << " " << actions[i].line.b.x << std::endl;

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

