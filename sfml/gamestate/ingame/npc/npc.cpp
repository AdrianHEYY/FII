#include <fstream>
#include "npc.h"

#include "../ingame.h"
#include "../../../util/util.h"
#include "../../../animation/animation.h"

#include <iostream>

npc::npc(in_game* ingame, std::string animation_name, std::string dialogue_file_text_name, sf::Vector2f position, sf::Vector2f size)
	: ingame(ingame), animation(animation_name, &sprite) {
	sprite.setPosition(position);
	sprite.setSize(size);
	animation.reset();

	current_dialogue = -1;

	std::ifstream in;
	in.open(dialogue_file_text_name);
	std::string input;
	while (getline(in, input)) {
		dialogue.push_back(input);
	}

	dialogue_box.setSize({500, 33});
	dialogue_box.setPosition(position - sf::Vector2f(dialogue_box.getSize().x / 2.0f, dialogue_box.getSize().y + 20));
	dialogue_box.setFillColor(sf::Color::Black);
	dialogue_box.setOutlineThickness(6);
	dialogue_box.setOutlineColor(sf::Color::White);

	dialogue_text.setFont(util::font);
	dialogue_text.setCharacterSize(30);
	dialogue_text.setFillColor(sf::Color::White);
	dialogue_text.setPosition(dialogue_box.getPosition()- sf::Vector2f(0, 2.5));
}

sf::Vector2f npc::get_pos() {
	return sprite.getPosition() + sprite.getSize() / 2.0f;
}

void npc::progress_dialogue() {
	if (util::keyboard::just_pressed(sf::Keyboard::E)) {
		current_dialogue ++;
		if (current_dialogue >= dialogue.size()) {
			is_done = 1;
			current_dialogue = dialogue.size() - 1;
		}
		if (is_done == 1) {

			dialogue_text.setString("I will forever be there with you.");
		}
		else {
			dialogue_text.setString(dialogue[current_dialogue]);
		}
		sf::Vector2f db_pos = dialogue_box.getPosition();
		sf::Vector2f db_size = dialogue_box.getSize();
		sf::Vector2f dt_pos = dialogue_text.getPosition();
		sf::FloatRect rect = dialogue_text.getGlobalBounds();
		dialogue_text.setPosition(sf::Vector2f(db_pos.x + db_size.x / 2.0f - rect.width / 2.0f, dt_pos.y));
	}
}

void npc::show_dialogue_box() {
	show_dialgoue = 1;
}

void npc::close_dialogue_box() {
	show_dialgoue = 0;
}

bool npc::done() {
	return is_done;
}

void npc::draw() {
	animation.update();
	util::window.draw(sprite);

	if (show_dialgoue == 1 && current_dialogue >= 0) {
		util::window.draw(dialogue_box);
		util::window.draw(dialogue_text);
	}
} 

npc::~npc() {

}