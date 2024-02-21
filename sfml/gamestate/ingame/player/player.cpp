#include "player.h"
#include "../ingame.h"

#include "playerstate/simplu/simplu.h"
#include "playerstate/olimpic/olimpic.h"
#include "playerstate/mic/mic.h"

player::player(in_game* game) {
	ingame = game;

	current_player = new Player_Simplu(this);
	velocity = sf::Vector2f(0.0f, 0.0f);

	current_player->get_sprite().setPosition(sf::Vector2f(util::window.getSize()) / 2.0f - current_player->get_sprite().getSize() / 2.0f);
}

void player::draw() {
	current_player->draw();
}
void player::update() {
	current_player->update();
	if (util::keyboard::just_released(sf::Keyboard::O)) {
		sf::Vector2f position = current_player->get_sprite().getPosition();

		current_player->~Player_State();
		current_player = new Player_Olimpic(this);

		current_player->get_sprite().setPosition(position);
	}
	else if (util::keyboard::just_released(sf::Keyboard::M)) {
		sf::Vector2f position = current_player->get_sprite().getPosition();

		current_player->~Player_State();
		current_player = new Player_Mic(this);

		current_player->get_sprite().setPosition(position);
	}
}