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
	BUCKET,
	ERASER
};

struct EventInfo {
	int mouseX;
	int mouseY;
	bool mouseDown;
	bool mouseUp;

	int tool = PENCIL;
	int timer = 0;

	bool inGame = true;

	bool capsLock = false;

	std::string guess = "";
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

struct GameState {
	int round;
	std::string currentWord;
	std::string drawingId;
	std::vector<Action> actions;
};