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
	inline sf::FloatRect getHitbox() { return current_player->get_hitbox(); };

	inline sf::Vector2f getVelocity() { return velocity; };
	inline void setVelocity(sf::Vector2f new_velocity) { velocity = new_velocity; };
	inline in_game* getIngame() { return ingame; };
	inline sf::Vector2f getOffPosition() { return off_position; };
	inline void setOffPosition(sf::Vector2f new_off_pos) { off_position = new_off_pos; };
private:
	in_game* ingame;
	Player_State* current_player = nullptr;

	sf::Vector2f velocity;
	sf::Vector2f off_position;
};