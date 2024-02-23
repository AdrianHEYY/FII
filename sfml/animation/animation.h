#pragma once

#include <string>
#include <chrono>
#include <vector>
#include <SFML/Graphics.hpp>

class Animation {
public:
	Animation(std::string filepath, sf::RectangleShape *sprite);
	void update();
	void reset();
private:
	std::vector<int> frame_times;
	int current_frame;
	std::chrono::high_resolution_clock::time_point last_time;
	sf::Texture tex;
	sf::RectangleShape* sprite;

	int frame_height, frame_width;
};