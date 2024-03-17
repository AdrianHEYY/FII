#pragma once

#include <SFML/Graphics.hpp>
#include "../../../animation/animation.h"
#include <vector>
#include <string>

extern class in_game;

class npc {
public:
	npc(in_game* ingame, std::string animation_name, std::string dialogue_file_text_name, sf::Vector2f position, sf::Vector2f size);
	void progress_dialogue();
	void draw();
	bool done();
	sf::Vector2f get_pos();
	void show_dialogue_box();
	void close_dialogue_box();
	~npc();
private:
	in_game* ingame;

	bool show_dialgoue;

	Animation animation;
	sf::RectangleShape sprite;

	std::vector<std::string> dialogue;
	int current_dialogue = 0;

	sf::RectangleShape dialogue_box;
	sf::Text dialogue_text;

	bool is_done = 0;
};