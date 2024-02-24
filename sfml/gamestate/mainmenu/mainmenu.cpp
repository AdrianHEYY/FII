#include "mainmenu.h"

#include "../../game/game.h"

main_menu::main_menu(Game* game)
{
	this->game = game;

	background.setSize(sf::Vector2f(util::window.getSize()));
	
    game_title.setSize(sf::Vector2f(300.0f,200.0f));
	game_title.setPosition(sf::Vector2f(util::window.getSize().x / 2 - game_title.getSize().x, game_title.getSize().y));
	

	play_button.setSize(sf::Vector2f(util::window.getSize())/10.0f);
	play_button.setFillColor(sf::Color::Blue);
	play_button.setPosition(sf::Vector2f(util::window.getSize()) / 2.0f - play_button.getSize() / 2.0f);
}

void main_menu::draw()
{
	util::window.draw(background);
	util::window.draw(game_title);
	util::window.draw(play_button);
}

void main_menu::update()
{
	sf::Vector2f cursor_location = sf::Vector2f(sf::Mouse::getPosition());
	float pos_x= cursor_location.x;
	float pos_y= cursor_location.y;

	sf::Vector2f play_button_pos = play_button.getPosition();
	float play_x1=play_button_pos.x;
	float play_x2=play_x1+play_button.getSize().x;

	float play_y1= play_button_pos.y;
	float play_y2= play_y1 + play_button.getSize().y;

	if((pos_x>=play_x1&&pos_x<=play_x2)&&(pos_y>=play_y1&&pos_y<=play_y2))
	{
		if (util::mouse::just_released()) {
			game->setGameState(game_states::IN_GAME);
		}
	}
}