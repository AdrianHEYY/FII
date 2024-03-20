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

	int selected = -1;

	sf::RectangleShape exit_buton;
	sf::Text exit_text;

	sf::RectangleShape resume_buton;
	sf::Text resume_text;

	sf::Text escape;
};