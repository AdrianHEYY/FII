#include "game.h"

#include "../gamestate/ingame/ingame.h"
#include "../gamestate/mainmenu/mainmenu.h"

Game::Game()
{
	current_game_state_ptr = new main_menu(this);


}

void Game::setGameState(game_states gamestate)
{
	switch(gamestate)
	{
	   case IN_GAME:
	   {
		   delete current_game_state_ptr;
		   current_game_state_ptr = new in_game(this);
	   }
	   break;
	   default:
		   current_game_state_ptr = new main_menu(this);
		   break;
	}
}
void Game::draw()
{
	current_game_state_ptr->draw();
}

void Game::update()
{
	current_game_state_ptr->update();
}