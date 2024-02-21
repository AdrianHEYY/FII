#pragma once

#include "../playerstate.h"

class Player_Mic : public Player_State {
public:
	Player_Mic(player* player_ptr);
	void update() override;
private:
	void update_movement();
};
