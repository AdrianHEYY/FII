#pragma once

#include <SFML/Graphics.hpp>

class Map {
public:
	Map();
	void draw();
	bool can_go(sf::Vector2f local_coord); // neimplementat
	void update(sf::Vector2f player_coord);
private:
	void setRect(int x, int y);
	sf::Image collision_map;
	sf::Texture texture_map;
	sf::RectangleShape sprite;

	const int screen_x = 480, screen_y = 270;
};