#pragma once

struct Point {
	int x;
	int y;
	Point(int x1, int y1) {
		x = x1;
		y = y1;
	}
};

struct Box {
	int x;
	int y;
	int w;
	int h;

	Box box(int x1, int y1, int w1, int h1) {
		x = x1;
		y = y1;
		w = w1;
		h = h1;
	}
};