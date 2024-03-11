#pragma once

#include "../gamestate.h"
#include "player/player.h"
#include "map/map.h"
#include "enemy/enemyflying/enemyflying.h"
#include "enemy/spike/spike.h"
#include "enemy/spitter/spitter.h"

class in_game : public game_state
{
public:
	in_game(Game* game);
	void draw() override;
	void update() override;

	sf::FloatRect map_empty_rect(sf::Vector2f pos, sf::Vector2f size);
	sf::FloatRect map_empty_rect(sf::FloatRect rect);
	inline sf::Vector2f convert_to_global_space(sf::Vector2f coord) { return map.convert_to_global_space(coord); };
	inline sf::Vector2u convert_to_local_space(sf::Vector2f coord) { return map.convert_to_local_space(coord); }
private:
	player sprite;
	Map map;
	std::vector<Enemy*> enemies;
};