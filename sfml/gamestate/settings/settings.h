#pragma once

#include "../gamestate.h"

class options : public game_state {
public:
	options(Game* game);
	void draw() override;
	void update() override;
private:
	sf::View this_view;
	Game* game;
	sf::RectangleShape background;
	std::vector<sf::RectangleShape> butoane;
	std::vector<sf::Text> butoane_text;

	std::vector<sf::RectangleShape> butoane_binded;
	std::vector<sf::Text> text_binded;
};