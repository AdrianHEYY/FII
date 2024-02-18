#pragma once

#include "../gamestate.h"
#include "player/player.h"
#include "map/map.h"

class in_game : public game_state
{
public:
    in_game(Game* game);
	void draw() override;
	void update() override;
private:
	player sprite;
	Map map;
};