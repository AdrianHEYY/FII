#pragma once

#include "../gamestate.h"

class main_menu : public game_state
{
public:
	main_menu(Game * game);
	void draw() override;
	void update() override;
private:

	sf::RectangleShape play_button;
	sf::RectangleShape game_title;
	sf::RectangleShape background;

};