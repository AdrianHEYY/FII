#pragma once

#include "../playerstate.h"

class Player_Olimpic : public Player_State {
public:
	Player_Olimpic(player * player_ptr);
	void update() override;
private:
	void update_movement();
};
