#define CPPHTTPLIB_OPENSSL_SUPPORT
#include <iostream>
#include <chrono>
#include <thread>
#include <SFML/Graphics.hpp>
#include <vector>

#include "json.hpp"
#include "httplib.h"
#include "colors.h"
#include "structs.h"
#include "serialize.h"
#include "globals.h"
#include "text.h"
#include "draw.h"
#include "print.h"
#include "UI.h"
#include "events.h"

int main() {
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

	float FPS = 0;
	auto clock = sf::Clock{};
	float elapsedTime = 0;
	float targetTime = 1.0f / 60.0f;
	while (window.isOpen()) {
		if (eventInfo.timer % 5 == 0) {
			FPS = 1.f / clock.getElapsedTime().asSeconds();
		}
		elapsedTime += clock.getElapsedTime().asSeconds();
		clock.restart();
		if (elapsedTime >= targetTime) {
			elapsedTime -= targetTime;
			eventInfo.timer++;
			if (eventInfo.timer == 101) {
				eventInfo.timer = 0;
				if (drawing != ENTER_NAME) {
					httplib::Client cli("https://hackmt-doodle-server-958025035627.us-central1.run.app");
					auto stateResponse = cli.Get("/players/getgamestate/" + to_str(gameState.id) + "/" + to_str(gameState.actions.size()) + "/" + to_str(gameState.messages.size()));
					nlohmann::json gameData = nlohmann::json::parse(stateResponse->body);

					int round = gameData["roundNumber"];
					if (round != gameState.round) {
						auto transitionResponse = cli.Get("/state/transition");
						nlohmann::json transitionData = nlohmann::json::parse(transitionResponse->body);

						gameState.drawingId = transitionData["drawerId"];
						gameState.wordOptions = transitionData["chosenWords"];

						if (gameState.wordOptions.size() > 0) {
							drawing = PICK_WORD;
						}

						gameState.round = round;
					}

					gameState.currentWord = gameData["word"];

					std::vector<Message> messages = gameData["newMessages"];
					auto actionList = gameData["newActions"];

					for (auto msg : messages) {
						gameState.messages.push_back(msg);
					}

					//for (Action action : actionList) {
					//	gameState.actions.push_back(action);
					//}
				}
			}
		}
		std::this_thread::sleep_for(std::chrono::milliseconds(1));

		if (numVertices > vertSize) {
			vertSize = numVertices + 1000;
			vertices.resize(vertSize);
			std::cout << "Increasing the size of the vertex buffer!" << std::endl;
		}

		handleEvents(&window);
		
		texture.clear(UI_BACKGROUND);

		drawUI();
		
		//drawLine(Point(90, 90), Point(eventInfo.mouseX, eventInfo.mouseY), 12, sf::Color::Red);

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