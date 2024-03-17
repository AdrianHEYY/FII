#pragma once

#include <SFML/Graphics.hpp>

namespace util {
	bool rect_collision(sf::RectangleShape& a, sf::RectangleShape& b);
	float convert_ms_to_frames(int ms);

	//extern sf::RenderWindow window;
	extern sf::RenderTexture window;
	extern sf::RenderWindow renderwindow;
	

	extern sf::Font font;
	extern float delta_time;
};