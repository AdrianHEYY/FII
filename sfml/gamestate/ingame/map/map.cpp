#include "map.h"


#include "../../../util/util.h"

Map::Map() {
	collision_map.loadFromFile("samples/collision_map.png");
	texture_map.loadFromFile("samples/texture_map.png");
	sprite.setTexture(&texture_map);
	
	sprite.setPosition({ 0, 0 });
	sprite.setSize(sf::Vector2f(util::window.getSize()));

	setRect(0, 0);
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
bool Map::can_go(sf::Vector2f coord) {
	sf::Vector2f local_coord = sf::Vector2f(screen_x * coord.x / 1920.0f, screen_y * coord.y / 1080.0f);

	sf::Vector2u ucoord = sf::Vector2u(local_coord);
	sf::Color col = collision_map.getPixel(ucoord.x, ucoord.y);
	if (col.r == 0 && col.g == 0 && col.b == 0) {
		return 0;
	}
	return 1;
}