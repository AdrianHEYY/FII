#include "game.h"

#include "../gamestate/ingame/ingame.h"
#include "../gamestate/mainmenu/mainmenu.h"
#include "../gamestate/settings/settings.h"
Game::Game()
{
	current_game_states.push_back(new main_menu(this));
}

void Game::setGameState(game_states gamestate)
{
	switch(gamestate)
	{
	   case IN_GAME:
	   {
		   delete current_game_states[current_game_states.size() - 1];
		   current_game_states.pop_back();

		   current_game_states.push_back(new in_game(this));
	   }
	   break;
	   default:
		   current_game_states.push_back(new main_menu(this));
		   break;
	}
}
#include <iostream>
void Game::draw()
{
	for (int i1 = 0; i1 < current_game_states.size(); i1++) {
		game_state* i = current_game_states[i1];
		i->draw();
	}
}
void Game::update()
{
	current_game_states[current_game_states.size() - 1]->update();
	if (util::keyboard::just_pressed(sf::Keyboard::O)) {
		auto top = current_game_states[current_game_states.size() - 1];
		if (dynamic_cast<options*>(top) == nullptr) {
			current_game_states.push_back(new options(this));
		}
	};
}