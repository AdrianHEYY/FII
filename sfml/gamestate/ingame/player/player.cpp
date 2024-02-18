#include "player.h"
#include "../ingame.h"

#include "playerstate/simplu/simplu.h"

player::player(in_game* game) {
	ingame = game;

	current_player = new Player_Simplu();
	velocity = sf::Vector2f(0.0f, 0.0f);

	current_player->get_sprite().setPosition(sf::Vector2f(util::window.getSize()) / 2.0f - current_player->get_sprite().getSize() / 2.0f);
}

void player::draw() {
	current_player->draw();
}

#include <iostream>

void player::update() {
	sf::View view = util::window.getView();
	std::cout << velocity.x << '\n';
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
	sf::Vector2f current_pos = current_player->get_sprite().getPosition();
	if (ingame->map_empty_rect(current_pos + velocity, current_player->get_sprite().getSize()) == 0) {
		velocity.x = 0;
	}

	static bool jumping = 0;

	if (jumping == 0) {
		velocity.y++;
		if (velocity.y > 10) velocity.y = 10;
		if (ingame->map_empty_rect(current_pos + velocity, current_player->get_sprite().getSize()) == 0) {
			velocity.y = 0; // pe pamant
			if (util::keyboard::just_pressed(sf::Keyboard::Key::Space)) {
				velocity.y -= 10;
				jumping = 1;
			}
		}
	}
	else {
		velocity.y += 0.3;
		if (velocity.y > 0) velocity.y = 0, jumping = 0;
		if (ingame->map_empty_rect(current_pos + velocity, current_player->get_sprite().getSize()) == 0) {
			//tavan ?
			velocity.y = 0;
			jumping = 0;
		}
	}

	current_player->get_sprite().setPosition(current_pos + velocity);
	off_position += velocity;
	view.move(velocity);

	util::window.setView(view);
}