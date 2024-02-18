#pragma once

#include "../util.h"

#include <SFML/Graphics.hpp>

namespace util {
	namespace keyboard
	{
		bool just_pressed(sf::Keyboard::Key key);
		bool just_released(sf::Keyboard::Key key);
		bool is_pressed(sf::Keyboard::Key key);
		void update_key(sf::Keyboard::Key key, bool just_pressed_key);
		void update_frame();
	}
};