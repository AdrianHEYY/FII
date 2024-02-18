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

	inline sf::Vector2f getPosition() { return current_player->get_sprite().getPosition(); };
	inline sf::Vector2f getOffPosition() { return off_position; };
private:
	in_game* ingame;
	Player_State* current_player = nullptr;

	sf::Vector2f velocity;
	sf::Vector2f off_position; // pentru a da la map
};