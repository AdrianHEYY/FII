#pragma once

#include "../gamestate.h"

class main_menu : public game_state
{
public:
	main_menu(Game* game);
	void draw() override;
	void update() override;
private:
	sf::View this_view;

	sf::RectangleShape play_button;
	sf::Text play_text;

	sf::RectangleShape quit_button;
	sf::Text quit_text;

	sf::RectangleShape options_button;
	sf::Text options_text;

	sf::Text game_title;

	sf::RectangleShape background;

};