#include "playerstate.h"

#include "../../../../util/util.h"

#include "../../player/player.h"

Player_State::Player_State(player * player_ptr) {
	this->player_ptr = player_ptr;
}
Player_State::Player_State() {

}

void Player_State::draw() {
	util::window.draw(sprite);
	
	// vvv hitbox vvv
	sf::RectangleShape rect;
	sf::Vector2f oldPos = sprite.getPosition();
	rect.setPosition(hitbox_sprite_offset + oldPos);
	rect.setSize(hitbox_size);
	rect.setFillColor(sf::Color(0, 255, 0, 122));
	util::window.draw(rect);
}

void Player_State::update() {

}