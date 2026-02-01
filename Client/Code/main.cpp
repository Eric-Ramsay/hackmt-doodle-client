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
#include "globals.h"
#include "text.h"
#include "draw.h"
#include "print.h"
#include "UI.h"
#include "events.h"

int main() {
	// HTTPS
	httplib::Client cli("https://localhost:7151");

	nlohmann::json playerName;
	std::string name;
	std::cout << "Player Name: ";
	std::cin >> name;
	playerName["name"] = name;
	
	auto nameResponse = cli.Post("/players", playerName.dump(), "application/json");

	if (nameResponse){
		if (nameResponse->status == 200){
			std::cout << "Success!" << std::endl;
		} else {
			std::cout << "Res->status:" << std::endl;
		}

		auto jsonResponse = nlohmann::json::parse(nameResponse->body);
		int clientId = jsonResponse["clientId"];

		std::cout << "Your client Id is: " << clientId << std::endl;
	} 


	//auto scoreResult = cli.Get("/players/scores");

	//if (scoreResult) {
	//	if (scoreResult->status == 200){
	//		std::cout << "Success!" << std::endl;
	//	} else {
	//		std::cout << "Res->status:" << std::endl;
	//	}
	//} else {
	//std::cout << "failed to send" << std::endl;
	//std::cout << "Res status: " << scoreResult->status << std::endl;
	//std::cout << "Error code: " << (int)scoreResult.error() << std::endl;
	//}

	//auto jsonScoreResponse = nlohmann::json::parse(scoreResult->body);
	//int score = jsonScoreResponse[std::to_string(clientId)];
	//std::cout << "Your score is: " << score << std::endl;
	//
	//std::string tempGuess;
	//nlohmann::json wordGuess;
	//std::cout << "Enter Guess: " << std::endl;
	//std::cin >> tempGuess;
	//wordGuess["guess"] = tempGuess;


	//auto guessResponse = cli.Post("/players/guess", wordGuess.dump(), "application/json");
	//if (guessResponse) {
	//	if (guessResponse->status == 200){
	//		std::cout << "Success!" << std::endl;
	//	} else {
	//		std::cout << "Res->status:" << std::endl;
	//	}
	//} else {
	//std::cout << "failed to send" << std::endl;
	//std::cout << "Res status: " << guessResponse->status << std::endl;
	//std::cout << "Error code: " << (int)guessResponse.error() << std::endl;
	//}

	//auto jsonGuessResponse = nlohmann::json::parse(guessResponse->body);
	//bool guess = jsonGuessResponse["correct"];

	//if (guess)
	//{
	//	std::cout << "Your guess was correct!" << std::endl;
	//} else
	//{
	//	std::cout << "Your guess was incorrect" << std::endl;
	//}


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

		print(to_str((int)FPS), 10, 200);
		print(to_str(eventInfo.timer), 10, 210);

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