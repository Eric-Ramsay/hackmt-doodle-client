#define CPPHTTPLIB_OPENSSL_SUPPORT
#include <iostream>
#include <chrono>
#include <thread>
#include <SFML/Graphics.hpp>
#include <vector>
#include <nlohmann/json.hpp>

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
	httplib::Client cli("http://localhost:5062");
	
	// if (auto res = cli.Get("/")) {
	// 	res->status;
	// 	res->body;
	// }

	nlohmann::json j;
	std::string name;
	std::cout << "Player Name: ";
	std::cin >> name;
	j["name"] = name;
	
	auto res = cli.Post("/players", j.dump(), "application/json");
	
	if (res){
		if (res->status == 200){
			std::cout << "Success!\n";
		} else {
			std::cout << "Res->status:";
		}
} else {
	std::cout << "failed to send\n";
	std::cout << "Res status: " << res->status << "\n";
	std::cout << "Error code: " << (int)res.error() << "\n";
}
	std::cout << "Waiting, input string: ";
	std::cin >> name;


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

		drawLine(Point(90, 90), Point(eventInfo.mouseX, eventInfo.mouseY), 12, sf::Color::Red);

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