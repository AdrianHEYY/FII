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
	sf::View view = util::window.getView();

	sf::Vector2f velocity = player_ptr->getVelocity();
	in_game* ingame = player_ptr->getIngame();

	if (util::keyboard::is_pressed(sf::Keyboard::A))
	{
		velocity.x--;
		if (velocity.x < -4)
			velocity.x = -4;
	}
	if (util::keyboard::is_pressed(sf::Keyboard::D))
	{
		velocity.x++;
		if (velocity.x > 4)
			velocity.x = 4;
	}
	if (!util::keyboard::is_pressed(sf::Keyboard::A) && !util::keyboard::is_pressed(sf::Keyboard::D) && velocity.x != 0)
	{
		velocity.x += ((velocity.x < 0) ? 1.0f : -1.0f);
	}

	sf::FloatRect current_hb = get_hitbox();

	sf::Vector2f current_pos(current_hb.left, current_hb.top);
	sf::Vector2f current_size(current_hb.width, current_hb.height);

	if (ingame->map_empty_rect(current_pos + velocity, current_size) == 0) {
		velocity.x = 0;
	}

	static bool jumping = 0;

	if (jumping == 0) {
		//todo: coliziunea astea e MEREU cu un pixel mai sus decat hitboxul la mapa si e asa de enervant
		// nush ce sa-i fac ca sa o rezolv fara sa pun doar hitboxul in sice astfel incat sa merga bine
		velocity.y += 1;
		if (velocity.y > 10) velocity.y = 10;

		if (ingame->map_empty_rect(current_pos + velocity,
			current_size) == 0) {
			velocity.y = 0; // pe pamant
			if (util::keyboard::just_pressed(sf::Keyboard::Key::Space)) {
				velocity.y -= 13;
				jumping = 1;
			}
		}

	}
	else {
		velocity.y += 0.3;

		if (velocity.x > -8 && velocity.x < 8)
			velocity.x *= 2;

		if (velocity.y > 0) velocity.y = 0, jumping = 0;
		if (velocity.y >= 0 && ingame->map_empty_rect(current_pos + velocity, current_size) == 0) {
			velocity.y = 0;
			jumping = 0;
		}
		//todo: coliziune tavan, doar ia punctele de sus in loc de toate plm
	}

	move(velocity);

	view.move(velocity);

	player_ptr->setVelocity(velocity);
	player_ptr->setOffPosition(player_ptr->getOffPosition() + velocity);

	util::window.setView(view);
}