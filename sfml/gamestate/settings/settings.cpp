#include "settings.h"

#include "../../util/util.h"
#include "../../util/keyboard/keyboard.h"
#include "../../util/mouse/mouse.h"

#include <iostream>
options::options(Game* game) 
: game(game) {
	background.setFillColor(sf::Color(255, 255, 255, 122));
	background.setOutlineColor(sf::Color::White);
	background.setOutlineThickness(6.0f);
	background.setSize(sf::Vector2f(util::window.getSize().x / 2.0f, util::window.getSize().y * 0.8));
	sf::Vector2f win_size = sf::Vector2f(util::window.getSize());
	background.setPosition(win_size / 2.0f - background.getSize() / 2.0f);
	
	//std::vector<sf::RectangleShape> butoane;
	//std::vector<sf::Text> butoane_text;
	for (int i = 0; i < 7; i++) {
		sf::RectangleShape buton;
		buton.setSize({ 300.0f, 40.0f });
		buton.setPosition(background.getPosition() + sf::Vector2f(100.0f, 100.0f + i * 70.0f));
		buton.setFillColor(sf::Color::Black);
		buton.setOutlineColor(sf::Color::White);
		buton.setOutlineThickness(4.0f);
		butoane.push_back(buton);	

		sf::RectangleShape buton_bind;
		buton_bind.setSize({ 40.0f, 40.0f });
		buton_bind.setPosition(buton.getPosition() +sf::Vector2f(buton.getSize().x, 0) + sf::Vector2f(30.0f, 0.0f));
		buton_bind.setFillColor(sf::Color::Black);
		buton_bind.setOutlineColor(sf::Color::White);
		buton_bind.setOutlineThickness(4.0f);
		butoane_binded.push_back(buton_bind);

		sf::Text text;
		text.setFont(util::font);
		text.setCharacterSize(30);
		switch (i) {
		case 0:
			text.setString("Move left");
			break;
		case 1:
			text.setString("Move right");
			break;
		case 2:
			text.setString("Jump");
			break;
		case 3:
			text.setString("Wall grab");
			break;
		case 4:
			text.setString("Crouch");
			break;
		case 5:
			text.setString("Charge jump");
			break;
		case 6:
			text.setString("Dash");
			break;
		default:
			text.setString(" ");
			break;
		}
		text.setPosition(buton.getPosition() + sf::Vector2f(20.0f, 0.0f));
		butoane_text.push_back(text);

		sf::Text text_bind;
		text_bind.setFont(util::font);
		text_bind.setCharacterSize(30);
		text_bind.setPosition(buton_bind.getPosition() + sf::Vector2f(10, 0));
		text_bind.setString("A");
		text_binded.push_back(text_bind);
	}

	this_view = sf::View(win_size / 2.0f, win_size);
}
void options::draw() {
	sf::View old_view = util::window.getView();

	util::window.setView(this_view);
	util::window.draw(background);
	for (int i = 0; i < butoane.size(); i++) {
		util::window.draw(butoane[i]);
		util::window.draw(butoane_text[i]);
		util::window.draw(butoane_binded[i]);
		util::window.draw(text_binded[i]);
	}

	util::window.setView(old_view);
}
void options::update() {
	
}