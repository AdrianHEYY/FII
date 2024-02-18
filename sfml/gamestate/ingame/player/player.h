#pragma once
#include <SFML/Graphics.hpp>

#include "playerstate/playerstate.h"

extern class in_game;

class player
{
public:
	player(in_game* game);
	void draw();
	void update();

private:
	Player_State* current_player = nullptr;

	sf::Vector2f velocity;
};