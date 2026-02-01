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
	Point(int x1, int y1) {
		x = x1;
		y = y1;
	}
	Point() {
		x = 0;
		y = 0;
	}
};

struct Line {
	Point a;
	Point b;
};

struct Action {
	TOOL tool;
	Line line;
	int width;
	std::string color;
};

struct GameState {
	int round;
	std::string currentWord;
	std::string drawingId;
	std::vector<Action> actions;
};