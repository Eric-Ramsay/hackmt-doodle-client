#pragma once

std::vector<sf::Vertex> vertices;
std::vector<Action> actions;

int numVertices = 0;
int vertSize = 200000;

const int WIDTH = 640;
const int HEIGHT = 360;
const int CANVAS_X = 2;
const int CANVAS_Y = 2;
const int CANVAS_W = 400;
const int CANVAS_H = HEIGHT - 4;


EventInfo eventInfo;