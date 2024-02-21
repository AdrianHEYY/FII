#include "ingame.h"

in_game::in_game(Game* game) 
	:sprite(this)
{
	this->game = game;
}

void in_game::draw() 
{
	map.draw();
	sprite.draw();
}

void in_game::update() 
{
	sprite.update();
	map.update(sprite.getOffPosition());
}

bool in_game::map_empty_rect(sf::Vector2f poz_map, sf::Vector2f size) {
	if (!map.can_go(poz_map)) return 0;
	if (!map.can_go(poz_map + sf::Vector2f(size.x, 0))) return 0;
	if (!map.can_go(poz_map + sf::Vector2f(0, size.y))) return 0;
	if (!map.can_go(poz_map + size)) return 0;

	return 1;
}

bool in_game::map_empty_rect(sf::FloatRect rect) {
	sf::Vector2f poz_map(rect.left, rect.top);
	sf::Vector2f size(rect.width, rect.height);
	return map_empty_rect(poz_map, size);
}
