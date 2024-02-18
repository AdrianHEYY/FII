#pragma once

#include <SFML/Graphics.hpp>

namespace util 
{
	namespace mouse 
	{
		bool just_pressed();
		bool just_released();
		bool is_pressed();
		void update_frame();
		void update_state(sf::Mouse::Button button, bool just_pressed);
		bool is_hovering(sf::RectangleShape &rect);
	}
}