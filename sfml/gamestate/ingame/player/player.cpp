#include "player.h"
#include "../ingame.h"

#include "playerstate/simplu/simplu.h"
#include "playerstate/olimpic/olimpic.h"
#include "playerstate/mic/mic.h"

player::player(in_game* game) {
	ingame = game;

	current_player = new Player_Simplu(this);
	velocity = sf::Vector2f(0.0f, 0.0f);

	// 8k 4k
	sf::Vector2f start_pos = sf::Vector2f(8000.0f, 4000.0f);
	
	off_position = sf::Vector2f(start_pos);
	current_player->get_sprite().setPosition(sf::Vector2f(start_pos));
	sf::View view = util::window.getView();
	view.move(sf::Vector2f(start_pos));
	util::window.setView(view);
	velocity = sf::Vector2f(0.0f, 0.0f);
	
	current_player->get_sprite().setPosition(start_pos + sf::Vector2f(util::window.getSize()) / 2.0f - current_player->get_sprite().getSize() / 2.0f);
}

void player::draw() {
	current_player->draw();
}
#include <iostream> //todo
void player::update() {
	sf::Vector2f pos = current_player->get_sprite().getPosition();
	std::cout << pos.x << ' ' << pos.y << '\n';
	current_player->update();
	if (1 == 0) { //todo
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
}