#include "mainmenu.h"

#include "../../game/game.h"

#include<iostream>

main_menu::main_menu(Game* game)
{
	this->game = game;

	background.setSize(sf::Vector2f(util::window.getSize()));
	background.setFillColor(sf::Color::Black);

	game_title.setFont(util::font);
	game_title.setCharacterSize(70);
	game_title.setString("New world");
	game_title.setPosition(sf::Vector2f(util::window.getSize().x / 2 - 150, 300));

	play_button.setSize(sf::Vector2f(util::window.getSize()) / 10.0f);
	play_button.setOutlineThickness(-8);
	play_button.setFillColor(sf::Color::Black);
	play_button.setOutlineColor(sf::Color::White);
	play_button.setPosition(sf::Vector2f(util::window.getSize()) / 2.0f - play_button.getSize() / 2.0f);

	play_text.setFont(util::font);
	play_text.setCharacterSize(70);
	play_text.setString("Play");
	play_text.setPosition(play_button.getPosition() + sf::Vector2f(25, 5));

}

void main_menu::draw()
{
	util::window.draw(background);

	util::window.draw(game_title);

	util::window.draw(play_button);
	util::window.draw(play_text);
}

void main_menu::update()
{
	sf::Vector2f cursor_location = sf::Vector2f(sf::Mouse::getPosition());
	float pos_x = cursor_location.x;
	float pos_y = cursor_location.y;

	sf::Vector2f play_button_pos = play_button.getPosition();
	float play_x1 = play_button_pos.x;
	float play_x2 = play_x1 + play_button.getSize().x;

	float play_y1 = play_button_pos.y;
	float play_y2 = play_y1 + play_button.getSize().y;

	if ((pos_x >= play_x1 && pos_x <= play_x2) && (pos_y >= play_y1 && pos_y <= play_y2))
	{
		if (util::mouse::just_released()) {
			game->setGameState(game_states::IN_GAME);
		}
	}
}