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
void Map::update(sf::Vector2f player_coord) {
	setRect(player_coord.x, player_coord.y);
}
void Map::setRect(int x, int y) {
	sprite.setTextureRect(sf::IntRect(x, y, x + screen_x, y + screen_x));
}
void Map::draw() {
	util::window.draw(sprite);
}
bool Map::can_go(sf::Vector2f local_coord) {
	return 1;
}