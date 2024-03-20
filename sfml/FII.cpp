#include <vector>
#include <string>
#include <thread>

#include <SFML/Graphics.hpp>

#include "util/util.h"
#include "util/keyboard/keyboard.h"
#include "util/mouse/mouse.h"
#include "util/shaders/shaders.h"

#include "game/game.h"

#include "button/button.h"

#include <chrono>

void preciseSleep(float seconds) {
	float ms = seconds * 1000;

	using namespace std;
	using namespace std::chrono;
	chrono::high_resolution_clock::time_point inainte, dupa;
	float took = 0;

	while (ms > 25) {
		inainte = chrono::high_resolution_clock::now();
		this_thread::sleep_for(chrono::milliseconds(1));
		dupa = chrono::high_resolution_clock::now();
		took = float(chrono::duration_cast<chrono::microseconds>(dupa - inainte).count()) / 1000.0;
		ms -= took;
	}

	inainte = chrono::high_resolution_clock::now();
	while (ms - float(chrono::duration_cast<chrono::microseconds>(chrono::high_resolution_clock::now() - inainte).count()) / 1000.0 > 0) {
		;
	}
}

int main() {
	util::font.loadFromFile("samples/Roboto-Medium.ttf");
	util::window.create(1920, 1080);

	Game game;

	float fps = 144;
	float frame_should_last_ms = 1000.0 / 144.0;

	std::chrono::high_resolution_clock::time_point last_frame = std::chrono::high_resolution_clock::now();

	//sf::Shader vignette;
	//vignette.loadFromFile("shaders/vignette.vert", "shaders/vignette.frag");
	//vignette.setUniform("iResolution", sf::Vector2f(1920, 1080));

	util::shaders::init();

	while (util::renderwindow.isOpen()) {
		sf::Event ev;
		util::keyboard::update_frame();
		util::mouse::update_frame();
		while (util::renderwindow.pollEvent(ev)) {
			switch (ev.type) {
			case sf::Event::Closed:
				util::renderwindow.close();
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
		
		util::window.clear(sf::Color::Black);

		game.draw();

		util::window.display();

		sf::Texture tex = util::window.getTexture();
		sf::Sprite win_sprite;
		win_sprite.setTexture(tex);
		util::renderwindow.clear();
		util::renderwindow.draw(win_sprite);
		util::renderwindow.display();

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

	}

	return 0;
}