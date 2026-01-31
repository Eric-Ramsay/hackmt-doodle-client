#define CPPHTTPLIB_OPENSSL_SUPPORT
#include <iostream>
#include <chrono>
#include <thread>
#include <SFML/Graphics.hpp>
#include <vector>

#include "httplib.h"
#include "colors.h"
#include "structs.h"
#include "globals.h"
#include "text.h"
#include "draw.h"
#include "UI.h"

int main() {
	// HTTPS
	httplib::Client cli("https://www.google.com");

	if (auto res = cli.Get("/")) {
		res->status;
		res->body;
	}

	const int SCREEN_W = sf::VideoMode::getDesktopMode().width;
	const int SCREEN_H = sf::VideoMode::getDesktopMode().height;

	const int SCALE_X = SCREEN_W / WIDTH;
	const int SCALE_Y = SCREEN_H / HEIGHT;

	sf::RenderWindow window;
	window.create(sf::VideoMode(SCREEN_W, SCREEN_H), "Doodle", sf::Style::Fullscreen);

	sf::Texture spriteSheet;
	spriteSheet.loadFromFile("./Assets/sprites.png");

	sf::RenderTexture texture;
	texture.create(WIDTH, HEIGHT);

	sf::Sprite sprite;
	sprite.setPosition(0, 0);
	sprite.setScale(SCALE_X, SCALE_Y);

	vertices.resize(vertSize);

	while (window.isOpen()) {
		std::this_thread::sleep_for(std::chrono::milliseconds(1));

		if (numVertices > vertSize) {
			vertSize = numVertices + 1000;
			vertices.resize(vertSize);
			std::cout << "Increasing the size of the vertex buffer!" << std::endl;
		}

		eventInfo.mouseX = sf::Mouse::getPosition().x / SCALE_X;
		eventInfo.mouseY = sf::Mouse::getPosition().y / SCALE_Y;
		eventInfo.mouseUp = false;
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window.close();
			}
			else if (event.type == sf::Event::LostFocus) {
				eventInfo.inGame = false;
			}
			else if (event.type == sf::Event::GainedFocus) {
				eventInfo.inGame = true;
			}
			if (eventInfo.inGame) {
				if (event.type == sf::Event::MouseButtonPressed) {
					if (event.mouseButton.button == sf::Mouse::Left) {
						eventInfo.mouseDown = true;
					}
				}
				if (event.type == sf::Event::MouseButtonReleased) {
					if (event.mouseButton.button == sf::Mouse::Left) {
						eventInfo.mouseDown = false;
						eventInfo.mouseUp = true;
					}
				}
				if (event.type == sf::Event::KeyPressed) {
					int keyCode = (int)event.key.code;
					char c = 0;

					if (keyCode >= sf::Keyboard::A && keyCode <= sf::Keyboard::Z) {
						char add = 'a';
						if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift)) {
							add = 'A';
						}
						c = add + (keyCode - (int)sf::Keyboard::A);
					}
					else if (keyCode >= sf::Keyboard::Num0 && keyCode <= sf::Keyboard::Num9) {
						c = (char)(keyCode - sf::Keyboard::Num0 + '0');
					}
					else if (keyCode == sf::Keyboard::Space) {
						c = (char)(keyCode - sf::Keyboard::Space + ' ');
					}
					else if (event.key.code == sf::Keyboard::Backspace) {
						if (eventInfo.guess.size() > 0) {
							eventInfo.guess.pop_back();
						}
					}
					if (c != 0 && eventInfo.guess.size() < 25) {
						eventInfo.guess += c;
					}
				}
			}
		}
		
		texture.clear(UI_BACKGROUND);

		drawUI();

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