#include <fstream> 
//#include <iostream>

#include "map.h"

#include "../../../util/util.h"

Map::Map() {

	texture_map.loadFromFile("samples/mapa_finala.png");
	sprite.setTexture(&texture_map);

	sprite.setPosition({ 0, 0 });
	sprite.setSize(sf::Vector2f(util::window.getSize()));

	setRect(0, 0);
}
void Map::add_wall_collision(int a, int b, int c, int d) {

	walls.push_back(sf::IntRect(a, b, c - a, d - b));
}

void Map::update(sf::Vector2f player_pos) {
	sprite.setPosition(player_pos);
	setRect(player_pos.x * screen_x / 1920, player_pos.y * screen_y / 1080);
}
void Map::setRect(int x, int y) {
	sprite.setTextureRect(sf::IntRect(x, y, screen_x, screen_y));
}
void Map::draw() {
	util::window.draw(sprite);
}

sf::FloatRect Map::intersects_walls(sf::FloatRect rect) { 
	sf::Vector2f st_sus(rect.left, rect.top);
	sf::Vector2f size(rect.width, rect.height);

	sf::Vector2u a = convert_to_local_space(st_sus);
	sf::Vector2u b = convert_to_local_space(size);
	
	sf::IntRect u(a.x, a.y, b.x, b.y);

	auto intersects = [&](sf::IntRect& a, sf::IntRect& b) -> bool {
		if (a.left + a.width < b.left || b.left + b.width < a.left)
			return false;
		if (a.top + a.height < b.top || b.top + b.height < a.top)
			return false;
		return true; 
	};

	for (auto& i : walls) {
		if (intersects(i, u) == 1) {
			return sf::FloatRect(sf::Vector2f(convert_to_global_space(sf::Vector2f(i.left, i.top))), 
				sf::Vector2f(convert_to_global_space(sf::Vector2f(i.width, i.height))));
		}
	}

	return sf::FloatRect(0, 0, 0, 0);
}