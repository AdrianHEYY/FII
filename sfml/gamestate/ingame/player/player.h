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

	inline void unlock_wall_jump() { can_wall_grab = 1; };
	inline void unlock_big_jump() { can_big_jump = 1; };
	inline void unlock_crouch() { can_crouch = 1; };
	inline void unlock_dash() { can_dash = 1; };
	
	inline sf::Vector2f getPosition() { return sprite.getPosition(); };
	inline sf::Vector2f getSize() { return sprite.getSize(); }
	inline sf::Vector2f getOffPosition() { return off_position; };
	inline sf::Vector2f getVelocity() { return velocity; };

	void respawn_go_location(sf::Vector2f location);

	inline sf::FloatRect get_hitbox() {
		if (is_crouching == 0) {
			return sf::FloatRect(sprite.getPosition().x + hitbox_sprite_offset.x,
				sprite.getPosition().y + hitbox_sprite_offset.y,
				hitbox_size.x,
				hitbox_size.y);
		}
		else { // dau crouch
			return sf::FloatRect(sprite.getPosition().x + hitbox_crouch_offset.x,
				sprite.getPosition().y + hitbox_crouch_offset.y,
				hitbox_crouch_size.x,
				hitbox_crouch_size.y);
		}
		return sf::FloatRect(0, 0, 0, 0);
	};
private:
	inline void move(sf::Vector2f offset) { sprite.setPosition(sprite.getPosition() + offset); };
	void update_movement();

	void update_movement_AD(sf::Vector2f& velocity);
	void update_movement_crouch(bool& check_jump, sf::Vector2f& velocity);
	bool can_go(sf::Vector2f new_pos, sf::Vector2f size);

	in_game* ingame;

	sf::Vector2f velocity;
	sf::Vector2f off_position;

	bool facing = 0; // 0 = left, 1 = right

	bool can_big_jump = 1;
	bool big_jumping = 0;
	bool big_jumping_done = 0;
	std::chrono::high_resolution_clock::time_point big_jump_time; // start_time

	bool can_wall_grab = 1;
	bool wall_grab = 0;
	bool wall_grab_direction = 0; // 0 = left, 1 = right
	sf::FloatRect wall_grab_wall;

	bool can_crouch = 1;
	bool is_crouching = 0;

	bool can_dash = 1;
	bool dashing = 0;
	bool has_dash = 0;
	std::chrono::high_resolution_clock::time_point dash_time; // start_time

	bool on_ground = 0;

	sf::RectangleShape sprite;
	sf::Texture texture;

	sf::Vector2f hitbox_size;
	sf::Vector2f hitbox_sprite_offset;

	sf::Vector2f hitbox_crouch_size;
	sf::Vector2f hitbox_crouch_offset;

	Animation animation_walk;
	Animation animation_idle;
	Animation animation_crouch;

	Animation animation_jump;
	Animation animation_fall;
	
	Animation animation_slide_wall;

	Animation animation_charge_jump;
	Animation animation_charge_idle;

	Animation animation_death;
	sf::Text death_text;
	bool dead = 0;
};