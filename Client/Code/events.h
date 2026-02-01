#pragma once

void handleEvents(sf::RenderWindow* window) {

	const int SCREEN_W = sf::VideoMode::getDesktopMode().width;
	const int SCREEN_H = sf::VideoMode::getDesktopMode().height;

	const int SCALE_X = SCREEN_W / WIDTH;
	const int SCALE_Y = SCREEN_H / HEIGHT;

	eventInfo.mouseX = sf::Mouse::getPosition().x / SCALE_X;
	eventInfo.mouseY = sf::Mouse::getPosition().y / SCALE_Y;
	eventInfo.mouseUp = false;
	sf::Event event;
	while (window->pollEvent(event)) {
		if (event.type == sf::Event::Closed) {
			window->close();
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
					newDraw = true;
				}
			}
			if (event.type == sf::Event::MouseButtonReleased) {
				if (event.mouseButton.button == sf::Mouse::Left) {
					eventInfo.mouseDown = false;
					eventInfo.mouseUp = true;
					newDraw = false;
					if (actions.size() > 0 && actions[actions.size() - 1].tool != BUCKET && actions[actions.size() - 1].line.b.x == 0 && actions[actions.size() - 1].line.b.y == 0) {
						actions.pop_back();
					}
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
				else if (keyCode == sf::Keyboard::Up) {
					if (eventInfo.cursorSize < 12) {
						eventInfo.cursorSize++;
					}
				}
				else if (keyCode == sf::Keyboard::Down) {
					if (eventInfo.cursorSize > 3) {
						eventInfo.cursorSize--;
					}
				}
				else if (event.key.code == sf::Keyboard::Backspace) {
					if (eventInfo.guess.size() > 0) {
						eventInfo.guess.pop_back();
					}
				}
				if (event.key.code == sf::Keyboard::Enter && eventInfo.guess != "")
				{
					if (drawing == DRAW_UI) {
						httplib::Client cli("https://hackmt-doodle-server-958025035627.us-central1.run.app");

						nlohmann::json sendGuess;
						std::string guess;
						sendGuess["guess"] = guess;

						auto guessResult = cli.Post("/players/guess/" + gameState.id, sendGuess.dump(), "application/json");

						eventInfo.guess = "";
					}
					else if (drawing == ENTER_NAME) {
						httplib::Client cli("https://hackmt-doodle-server-958025035627.us-central1.run.app");
						nlohmann::json playerName;
						playerName["name"] = "test";

						auto nameResponse = cli.Post("/players", playerName.dump(), "application/json");

						if (nameResponse) {
							auto jsonResponse = nlohmann::json::parse(nameResponse->body);
							gameState.id = jsonResponse["clientId"];
						}

						eventInfo.guess = "";
						drawing = DRAW_UI;
					}

				}
				if (c != 0 && eventInfo.guess.size() < 30) {
					eventInfo.guess += c;
				}
			}
		}
	}
}
