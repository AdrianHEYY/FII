#pragma once
#include <SFML/Graphics.hpp>

#include "../../../animation/animation.h"

extern class in_game;

class player
{
public:
	player(in_game* game);
	void draw();
	void update();

	inline sf::Vector2f getPosition() { return sprite.getPosition(); };
	inline sf::Vector2f getOffPosition() { return off_position; };
	inline sf::Vector2f getVelocity() { return velocity; };

	//inline sf::RectangleShape& get_sprite() { return sprite; };
	inline sf::FloatRect get_hitbox() {
		return sf::FloatRect(sprite.getPosition().x + hitbox_sprite_offset.x,
			sprite.getPosition().y + hitbox_sprite_offset.y,
			hitbox_size.x,
			hitbox_size.y);
	};
private:
	inline void move(sf::Vector2f offset) { sprite.setPosition(sprite.getPosition() + offset); };
	void update_movement();

	void update_movement_AD(sf::Vector2f& velocity);
	bool can_go(sf::Vector2f new_pos, sf::Vector2f size);

	in_game* ingame;

	sf::Vector2f velocity;
	sf::Vector2f off_position;

	bool can_wall_grab = 1;
	bool wall_grab = 0;
	bool wall_grab_direction = 0; // 0 = left, 1 = right
	


	sf::RectangleShape sprite;
	sf::Texture texture;

	sf::Vector2f hitbox_size;
	sf::Vector2f hitbox_sprite_offset;

	Animation animation_walk;
	Animation animation_idle;
};