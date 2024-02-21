#pragma once

#include <SFML/Graphics.hpp>

enum player_states {
	SIMPLU, 
	GRAS,
	FURIOS
};

extern class player;

class Player_State {
public:
	Player_State(player * player_ptr);
	Player_State();

	inline sf::RectangleShape& get_sprite() { return sprite; };
	inline void move(sf::Vector2f offset) { sprite.setPosition(sprite.getPosition() + offset); }; 
	inline sf::FloatRect get_hitbox() { 
		return sf::FloatRect(sprite.getPosition().x + hitbox_sprite_offset.x,
			sprite.getPosition().y + hitbox_sprite_offset.y,
			hitbox_size.x,
			hitbox_size.y);
	};

	void draw();
	virtual void update();
private:
	
protected:
	player* player_ptr;

	sf::RectangleShape sprite;
	sf::Texture texture;

	sf::Vector2f hitbox_size;
	sf::Vector2f hitbox_sprite_offset;
};