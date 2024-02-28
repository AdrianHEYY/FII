#include <iostream>
#include <vector>
#include <string>
#include <thread>

#include <SFML/Graphics.hpp>

#include "util/util.h"
#include "util/keyboard/keyboard.h"
#include "util/mouse/mouse.h"

#include "game/game.h"

#include "button/button.h"

#include "chrono"
#include "Windows.h"

void preciseSleep(double seconds) { // not stolen code
	using namespace std;
	using namespace std::chrono;

	static double estimate = 5e-3;
	static double mean = 5e-3;
	static double m2 = 0;
	static int64_t count = 1;

	while (seconds > estimate) {
		auto start = high_resolution_clock::now();
		this_thread::sleep_for(milliseconds(1));
		auto end = high_resolution_clock::now();

		double observed = (end - start).count() / 1e9;
		seconds -= observed;

		++count;
		double delta = observed - mean;
		mean += delta / count;
		m2 += delta * (observed - mean);
		double stddev = sqrt(m2 / (count - 1));
		estimate = mean + stddev;
	}

	// spin lock
	auto start = high_resolution_clock::now();
	while ((high_resolution_clock::now() - start).count() / 1e9 < seconds);
}

int main() {
	Game game;

	util::font.loadFromFile("samples/Roboto-Medium.ttf");
	
	float fps = 144;
	float frame_should_last_ms = 1000.0 / 144.0;

	std::chrono::high_resolution_clock::time_point last_frame = std::chrono::high_resolution_clock::now();

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

		std::chrono::high_resolution_clock::time_point this_frame = std::chrono::high_resolution_clock::now();
		long long duration = std::chrono::duration_cast<std::chrono::milliseconds>(this_frame - last_frame).count();
		if (duration < frame_should_last_ms) {
			preciseSleep((frame_should_last_ms - duration) / 1000.0);
			std::chrono::high_resolution_clock::time_point now_time = std::chrono::high_resolution_clock::now();
			duration = std::chrono::duration_cast<std::chrono::milliseconds>(now_time - last_frame).count();
			last_frame = now_time;
		}
		else {
			last_frame = this_frame;
		}
		util::delta_time = duration / frame_should_last_ms;

		//std::cout << util::delta_time << '\n';
	}

	return 0;
}