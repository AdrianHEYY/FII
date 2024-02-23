#include "mic.h"

#include "../../../../../util/util.h"
#include "../../../../../util/keyboard/keyboard.h"
#include "../../player.h"
#include "././../../../ingame.h"

Player_Mic::Player_Mic(player* player_ptr) {
	this->player_ptr = player_ptr;

	texture.loadFromFile("samples/player_angry.png");
	sprite.setTexture(&texture);

	sf::Vector2f ss(30 * 2, 40 * 2);

	sprite.setSize(sf::Vector2f(ss.x, ss.y));

	hitbox_size = sprite.getSize();
	
	hitbox_size = sf::Vector2f(ss.x - ss.x/8, ss.y-ss.y/8);
	hitbox_sprite_offset = sf::Vector2f(6, 8);
}

void Player_Mic::update() {
	update_movement();
};
void Player_Mic::update_movement() {
	
}