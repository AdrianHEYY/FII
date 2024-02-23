#pragma once

#include <SFML/Graphics.hpp>

namespace util {
	bool rect_collision(sf::RectangleShape& a, sf::RectangleShape& b);
	extern sf::RenderWindow window;
	extern sf::Font font;
	extern float delta_time;
};