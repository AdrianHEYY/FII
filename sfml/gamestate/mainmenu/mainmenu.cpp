#include "mainmenu.h"

#include "../../game/game.h"

main_menu::main_menu(Game* game)
{
	this->game = game;

	background.setSize(sf::Vector2f(util::window.getSize()));
	background.setFillColor(sf::Color::Black);

	game_title.setFont(util::font);
	game_title.setCharacterSize(70);
	game_title.setString("New worlds");
	game_title.setPosition(sf::Vector2f(util::window.getSize().x / 2 - 150, 300));

	play_button.setSize(sf::Vector2f(util::window.getSize()) / 10.0f);
	play_button.setOutlineThickness(-8);
	play_button.setFillColor(sf::Color::Black);
	play_button.setOutlineColor(sf::Color::White);
	play_button.setPosition(sf::Vector2f(util::window.getSize()) / 2.0f - play_button.getSize() / 2.0f);

	quit_button.setSize(sf::Vector2f(util::window.getSize()) / 10.0f);
	quit_button.setOutlineThickness(-8);
	quit_button.setFillColor(sf::Color::Black);
	quit_button.setOutlineColor(sf::Color::White);
	quit_button.setPosition(play_button.getPosition() + sf::Vector2f(0.0, 150.0f));

	options_button.setSize(sf::Vector2f(util::window.getSize()) / 10.0f);
	options_button.setOutlineThickness(-4);
	options_button.setFillColor(sf::Color::Black);
	options_button.setOutlineColor(sf::Color::White);
	options_button.setPosition(quit_button.getPosition() + sf::Vector2f(0.0, 150.0f));

	play_text.setFont(util::font);
	play_text.setCharacterSize(70);
	play_text.setString("Play");
	play_text.setPosition(play_button.getPosition() + sf::Vector2f(25, 5));
	
	quit_text.setFont(util::font);
	quit_text.setCharacterSize(70);
	quit_text.setString("Quit");
	quit_text.setPosition(quit_button.getPosition() + sf::Vector2f(25, 5));

	options_text.setFont(util::font);
	options_text.setCharacterSize(40);
	options_text.setString("Settings");
	options_text.setPosition(options_button.getPosition() + sf::Vector2f(25, 25));

	sf::Vector2f win_size = sf::Vector2f(util::window.getSize());
	this_view = sf::View(win_size / 2.0f, win_size);
}

void main_menu::draw()
{
	sf::View old_view = util::window.getView();
	util::window.setView(this_view);

	util::window.draw(background);

	util::window.draw(game_title);

	util::window.draw(play_button);
	util::window.draw(play_text);
	
	util::window.draw(quit_button);
	util::window.draw(quit_text);

	util::window.draw(options_button);
	util::window.draw(options_text);

	util::window.setView(old_view);
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

	if (play_button.getGlobalBounds().contains(cursor_location) == 1 && util::mouse::just_pressed() == 1) {
		game->setGameState(IN_GAME);
	}
	if (quit_button.getGlobalBounds().contains(cursor_location) == 1 && util::mouse::just_pressed() == 1) {
		util::renderwindow.close();
	}
	if (options_button.getGlobalBounds().contains(cursor_location) == 1 && util::mouse::just_pressed() == 1) {
		game->setGameState(OPTIONS);
	}
}