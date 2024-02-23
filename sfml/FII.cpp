#include <iostream>
#include <vector>
#include <string>

#include <SFML/Graphics.hpp>

#include "util/util.h"
#include "util/keyboard/keyboard.h"
#include "util/mouse/mouse.h"

#include "game/game.h"

#include "button/button.h"

#include "chrono"
#include "Windows.h"

int main() {
	Game game;
	
	//util::window.setFramerateLimit(144);

	util::font.loadFromFile("samples/Roboto-Medium.ttf");
	
	float fps = 144.0;
	util::window.setFramerateLimit(144);
	sf::Clock delta_clock;

	while (util::window.isOpen()) {
		sf::Event ev;
		util::keyboard::update_frame();
		util::mouse::update_frame();
		while (util::window.pollEvent(ev)) {
			switch (ev.type) {
			case sf::Event::Closed:
				util::window.close();
				break;
			case sf::Event::KeyPressed:
				util::keyboard::update_key(ev.key.code, 1);
				break;
			case sf::Event::KeyReleased:
				util::keyboard::update_key(ev.key.code, 0);
				break;
			case sf::Event::MouseButtonPressed:
				util::mouse::update_state(ev.mouseButton.button, 1);
				break;
			case sf::Event::MouseButtonReleased:
				util::mouse::update_state(ev.mouseButton.button, 0);
				break;
			default:
				break; 
			}
		}

		game.update();
		
		util::window.clear(sf::Color::White);


		game.draw();

		util::window.display();

		if (util::keyboard::is_pressed(sf::Keyboard::Key::Escape)) util::window.close();

		long long duration = delta_clock.restart().asMilliseconds();
		long long ms_frame = (1000.0 / 144.0);
		if (duration < ms_frame) {
			Sleep(ms_frame - duration);
			duration = ms_frame;
		}
		util::delta_time = float(duration) / float(ms_frame);
	}

	return 0;
}