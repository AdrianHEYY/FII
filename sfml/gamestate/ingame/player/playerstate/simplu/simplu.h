#pragma once

#include "../playerstate.h"

class Player_Simplu : public Player_State {
public:
	Player_Simplu(player* player_ptr);
	void update() override;
private:
	void update_movement();
	void update_movement(float delta_time);

	Animation animation_walk;
	Animation animation_idle;
};