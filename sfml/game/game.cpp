#include "game.h"

#include "../gamestate/ingame/ingame.h"
#include "../gamestate/mainmenu/mainmenu.h"
#include "../gamestate/settings/settings.h"


Game::Game()
{
	setGameState(MAIN_MENU);
	next_remove_game_state = NONE;
}

void Game::setGameState(game_states gamestate)
{
	next_game_state = gamestate;
	if (current_game_states.size() > 0 && dynamic_cast<options*>(current_game_states[current_game_states.size() - 1]) != nullptr && next_game_state == OPTIONS) {
		next_game_state = NONE;
	}
}

void Game::removeGameState(game_states gamestate) {
	next_remove_game_state = gamestate;
}

void Game::draw()
{
	for (int i1 = 0; i1 < current_game_states.size(); i1++) {
		game_state* i = current_game_states[i1];
		i->draw();
	}
}
void Game::clear_states() {
	while (current_game_states.size() > 0) {
		if (dynamic_cast<in_game*>(current_game_states[current_game_states.size() - 1]) != nullptr) {
			dynamic_cast<in_game*>(current_game_states[current_game_states.size() - 1])->~in_game();
		}
		else
			delete current_game_states[current_game_states.size() - 1];
		current_game_states.pop_back();
	}
}
void Game::update()
{
	if (next_game_state != NONE) {
		switch (next_game_state) {
		case MAIN_MENU:
		{
			clear_states();
			current_game_states.push_back(new main_menu(this));
			break;
		}
		case IN_GAME:
		{
			clear_states();
			current_game_states.push_back(new in_game(this));
			break;
		}
		case OPTIONS:
		{
			current_game_states.push_back(new options(this));
			break;
		}
		};
		next_game_state = NONE;
	}
	if (next_remove_game_state != NONE) {
		switch (next_remove_game_state) {
		case OPTIONS:
		{
			delete current_game_states[current_game_states.size() - 1];
			current_game_states.pop_back();
			break;
		}
		};
		next_remove_game_state = NONE;
	}

	current_game_states[current_game_states.size() - 1]->update();
}