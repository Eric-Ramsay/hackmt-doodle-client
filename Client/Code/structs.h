#pragma once
#include <chrono>

struct Point {
	int x;
	int y;
	Point(int x1, int y1) {
		x = x1;
		y = y1;
	}
};

struct Line {
	Point a;
	Point b;
};

struct Action {
	std::string clientId;
	enum tool {
		eraser,
		pencil,
		bucket
	};
	int brushSize;
	Line points;
	std::string color;

};

struct Clients {
	std::string clientId;
	std::string name;
	int score;
	bool connected;
	std::chrono::system_clock::time_point lastTime;
};

struct GameState {
	std::string currentWord;
	int round;
	std::string drawingId;
	Action draw;
}; 