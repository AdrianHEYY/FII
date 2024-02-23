#pragma once

#include <SFML/Graphics.hpp>

class Map {
public:
	Map();
	void draw(); 
	sf::FloatRect intersects_walls(sf::FloatRect rect);
	void update(sf::Vector2f player_coord);
private:
	void setRect(int x, int y);
	inline sf::Vector2u convert_to_local_space(sf::Vector2f coord) { return sf::Vector2u(screen_x * coord.x / 1920, screen_y * coord.y / 1080); };
	inline sf::Vector2f convert_to_global_space(sf::Vector2f coord) { return sf::Vector2f(coord.x * 1920.0 / screen_x, coord.y * 1920.0 / screen_y); };
	sf::Texture texture_map;
	sf::RectangleShape sprite;
	
	std::vector<sf::IntRect> walls;

	const float screen_x = 480, screen_y = 270;
};