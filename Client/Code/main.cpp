#define CPPHTTPLIB_OPENSSL_SUPPORT
#include <iostream>
#include <chrono>
#include <thread>
#include <SFML/Graphics.hpp>
#include <vector>

#include "globals.h"
#include "structs.h"
#include "draw.h"
#include "httplib.h"

int main() {
	// HTTPS
	httplib::Client cli("https://www.google.com");

	if (auto res = cli.Get("/")) {
		res->status;
		res->body;
	}

	const int WIDTH = 640;
	const int HEIGHT = 360;

	const int SCREEN_W = sf::VideoMode::getDesktopMode().width;
	const int SCREEN_H = sf::VideoMode::getDesktopMode().height;

	sf::RenderWindow window;
	window.create(sf::VideoMode(SCREEN_W, SCREEN_H), "Doodle", sf::Style::Fullscreen);

	sf::Texture spriteSheet;
	spriteSheet.loadFromFile("./Assets/sprites.png");

	sf::RenderTexture texture;
	texture.create(WIDTH, HEIGHT);

	sf::Sprite sprite;
	sprite.setPosition(0, 0);
	sprite.setScale(SCREEN_W/WIDTH, SCREEN_H/HEIGHT);

	vertices.resize(vertSize);
	
	while (window.isOpen()) {
		std::this_thread::sleep_for(std::chrono::milliseconds(1));

		if (numVertices > vertSize) {
			vertSize = numVertices + 1000;
			vertices.resize(vertSize);
			std::cout << "Increasing the size of the vertex buffer!" << std::endl;
		}

		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window.close();
			}
		}
		
		texture.clear(sf::Color(30, 100, 180));

		drawSprite(0, 0, 16, 16, 1, 1);

		fillShape(Point(30, 30), Point(30, 50), Point(50, 30), Point(50, 50), sf::Color::Red);

		if (numVertices > 0) {
			texture.draw(&vertices[0], numVertices, sf::Triangles, &spriteSheet);
			numVertices = 0;
			texture.display();
			sprite.setTexture(texture.getTexture());
		}

		window.draw(sprite);

		window.display();
	}
	
	return 0;
}