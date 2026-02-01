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
				if (c != 0 && eventInfo.guess.size() < 30) {
					eventInfo.guess += c;
				}
			}
		}
	}
}