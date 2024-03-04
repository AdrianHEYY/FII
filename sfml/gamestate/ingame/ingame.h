#pragma once

#include "../gamestate.h"
#include "player/player.h"
#include "map/map.h"
#include "enemy/enemyflying/enemyflying.h"

class in_game : public game_state
{
public:
    in_game(Game* game);
	void draw() override;
	void update() override;

	sf::FloatRect map_empty_rect(sf::Vector2f pos, sf::Vector2f size);
	sf::FloatRect map_empty_rect(sf::FloatRect rect);
private:
	player sprite;
	Map map;
	std::vector<Enemy*> enemies;
};