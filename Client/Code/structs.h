#pragma once

struct Box {
	int x;
	int y;
	int w;
	int h;

	Box(int x1, int y1, int w1, int h1) {
		x = x1;
		y = y1;
		w = w1;
		h = h1;
	}
};

enum TOOL {
	PENCIL,
	ERASER,
	BUCKET
};

struct EventInfo {
	int mouseX;
	int mouseY;
	bool mouseDown;
	bool mouseUp;

	TOOL tool = PENCIL;
	int timer = 0;

	bool inGame = true;

	bool capsLock = false;

	std::string guess = "";

	int cursorSize = 3;
	std::string color = "green";
	std::string backgroundColor = "blue";
};

struct Point {
	int x;
	int y;
	Point(int x1 = 0, int y1 = 0) {
		x = x1;
		y = y1;
	}
};

struct Line {
	Point a;
	Point b;
	Line(Point a1 = Point(), Point b1 = Point()) {
		a = a1;
		b = b1;
	}
};

struct Action {
	TOOL tool;
	Line line;
	int width;
	std::string color;

	Action(Point a, Point b, int w, TOOL t, std::string c) {
		line = Line(a, b);
		width = w;
		tool = t;
		color = c;
	}
};

struct Message {
	bool succes;
	std::string text = "";
	int id;
};

struct GameState {
	int round;
	int timeRemaining;
	int score;
	int id;
	std::string currentWord = "_________ ______";
	int drawingId;
	std::vector<Action> actions;
	std::vector<Message> messages;
};

int min(int a, int b) {
	if (a < b) {
		return a;
	}
	return b;
 }

enum UI_STATE {
	ENTER_NAME,
	DRAW_UI,
	PICK_WORD
};