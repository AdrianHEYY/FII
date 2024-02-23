#include "olimpic.h"

#include "../../../../../util/util.h"
#include "../../../../../util/keyboard/keyboard.h"
#include "../../player.h"
#include "././../../../ingame.h"

Player_Olimpic::Player_Olimpic(player* player_ptr) {
	this->player_ptr = player_ptr;

	texture.loadFromFile("samples/1.jpg");
	sprite.setTexture(&texture);

	sprite.setSize(sf::Vector2f(48.0 * 2, 64.0 * 2));

	hitbox_size = sprite.getSize();
	hitbox_size = sf::Vector2f(48.0 * 2 - 12, 64.0 * 2 - 16);
	hitbox_sprite_offset = sf::Vector2f(6, 8);
}

void Player_Olimpic::update() {
	update_movement();
}
void Player_Olimpic::update_movement() {
	
}