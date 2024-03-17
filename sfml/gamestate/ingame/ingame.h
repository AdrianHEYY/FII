#pragma once

#include "../gamestate.h"
#include "player/player.h"
#include "map/map.h"
#include "enemy/enemyflying/enemyflying.h"
#include "enemy/spike/spike.h"
#include "enemy/spitter/spitter.h"
#include "npc/npc.h"

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
	inline std::vector<Enemy*> get_enemies() { return enemies; };

	void save_last_npc(int new_npc);
	
	void respawn_player();
private:
	player sprite;
	Map map;
	std::vector<Enemy*> enemies;
	npc* npcs[4] = {nullptr, nullptr, nullptr, nullptr};

	struct save_file {
		int last_npc_visited = -1;
		bool can_big_jump = 0;
		bool can_wall_jump = 0;
		bool can_crouch = 0;
		bool can_dash = 0;
	};
	save_file current_save_file;
};