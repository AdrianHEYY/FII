#include "settings.h"

#include "../../util/util.h"
#include "../../util/keyboard/keyboard.h"
#include "../../util/mouse/mouse.h"
#include "../../game/game.h"

options::options(Game* game) 
: game(game) {
	background.setFillColor(sf::Color(255, 255, 255, 40));
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

		sf::Text text_bind;
		text_bind.setFont(util::font);
		text_bind.setCharacterSize(30);
		text_bind.setPosition(buton_bind.getPosition() + sf::Vector2f(10, 0));

		sf::Text text;
		text.setFont(util::font);
		text.setCharacterSize(30);
		switch (i) {
		case 0:
			text.setString("Move left");
			text_bind.setString(util::keyboard::fromKtoS(util::keyboard::move_left_key));
			break;
		case 1:
			text.setString("Move right");
			text_bind.setString(util::keyboard::fromKtoS(util::keyboard::move_right_key));
			break;
		case 2:
			text.setString("Jump");
			text_bind.setString(util::keyboard::fromKtoS(util::keyboard::jump_key));
			break;
		case 3:
			text.setString("Wall grab");
			text_bind.setString(util::keyboard::fromKtoS(util::keyboard::wall_grab_key));
			break;
		case 4:
			text.setString("Crouch");
			text_bind.setString(util::keyboard::fromKtoS(util::keyboard::crouch_key));
			break;
		case 5:
			text.setString("Charge jump");
			text_bind.setString(util::keyboard::fromKtoS(util::keyboard::big_jump_key));
			break;
		case 6:
			text.setString("Dash");
			text_bind.setString(util::keyboard::fromKtoS(util::keyboard::dash_key));
			break;
		default:
			text.setString(" ");
			break;
		};
		text.setPosition(buton.getPosition() + sf::Vector2f(20.0f, 0.0f));
		butoane_text.push_back(text);

		text_binded.push_back(text_bind);
	}

	this_view = sf::View(win_size / 2.0f, win_size);


	sf::Vector2f stanga_jos = sf::Vector2f(background.getPosition() + sf::Vector2f(0, background.getSize().y));
	exit_buton.setPosition(stanga_jos + sf::Vector2f(100.0f, -100.0f));
	exit_buton.setSize(sf::Vector2f(100.0f, 40.0f));
	exit_buton.setFillColor(sf::Color::Black);
	exit_buton.setOutlineColor(sf::Color::White);
	exit_buton.setOutlineThickness(4.0f);

	resume_buton.setPosition(exit_buton.getPosition() + sf::Vector2f(500.0, 0.0));
	resume_buton.setSize(sf::Vector2f(150.0f, 40.0f));
	resume_buton.setFillColor(sf::Color::Black);
	resume_buton.setOutlineColor(sf::Color::White);
	resume_buton.setOutlineThickness(4.0f);

	exit_text.setPosition(stanga_jos + sf::Vector2f(125.0f, -100.0f));
	exit_text.setFont(util::font);
	exit_text.setCharacterSize(30);
	exit_text.setString("Exit");

	resume_text.setPosition(resume_buton.getPosition() + sf::Vector2f(23.0, 0.0));
	resume_text.setFont(util::font);
	resume_text.setCharacterSize(30);
	resume_text.setString("Resume");

	escape.setPosition(background.getPosition() + sf::Vector2f(10, 10));
	escape.setFont(util::font);
	escape.setString("Press Escape any time to enter the settings!\nPress E to interact with things!\nIn case you want to play faster through the game, you can press O to enter and exit godmode");
	escape.setCharacterSize(20);
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

	if (selected != -1) {
		sf::Text sel;
		sf::Vector2f but_pos = sf::Vector2f(background.getPosition() + sf::Vector2f(100.0f, 100.0f + selected * 70.0f));
		sf::Vector2f but_bind_pos = sf::Vector2f(but_pos + sf::Vector2f(300.0f, 0) + sf::Vector2f(30.0f, 0.0f));
		sel.setPosition(but_bind_pos + sf::Vector2f(60, 0));
		sel.setFont(util::font);
		sel.setCharacterSize(30);
		sel.setString("<");
		util::window.draw(sel);
	}

	util::window.draw(exit_buton);
	util::window.draw(exit_text);

	util::window.draw(resume_buton);
	util::window.draw(resume_text);

	util::window.draw(escape);

	util::window.setView(old_view);
}
void options::update() {
	sf::View old_view = util::window.getView();
	util::window.setView(this_view);
	sf::Vector2f m_pos = sf::Vector2f(sf::Mouse::getPosition(util::renderwindow));
	for (int i = 0; i < 7; i++) {
		if (butoane_binded[i].getGlobalBounds().contains(m_pos) == 1 && util::mouse::just_pressed() == 1) {
			if (selected != i)
				selected = i;
			else
				selected = -1;
		}
	}

	if (selected != -1 && util::keyboard::just_pressed_a_key == 1) {
		sf::Keyboard::Key just_pressed = util::keyboard::get_just_pressed_keys()[0];
		std::string code = util::keyboard::fromKtoS(just_pressed);
		if (code == "Unknown") {
			selected = -1;
		}
		else {
			switch (selected) {
			case 0:
				util::keyboard::move_left_key = just_pressed;
				break;
			case 1:
				util::keyboard::move_right_key = just_pressed;
				break;
			case 2:
				util::keyboard::jump_key = just_pressed;
				break;
			case 3:
				util::keyboard::wall_grab_key = just_pressed;
				break;
			case 4:
				util::keyboard::crouch_key = just_pressed;
				break;
			case 5:
				util::keyboard::big_jump_key = just_pressed;
				break;
			case 6:
				util::keyboard::dash_key = just_pressed;
				break;
			default:
				break;
			}
			text_binded[selected].setString(util::keyboard::fromKtoS(just_pressed));
			selected = -1;
		}
	}

	if (exit_buton.getGlobalBounds().contains(m_pos) == 1 && util::mouse::just_pressed() == 1) {
		game->setGameState(MAIN_MENU);
	}
	if (resume_buton.getGlobalBounds().contains(m_pos) == 1 && util::mouse::just_pressed() == 1) {
		game->removeGameState(OPTIONS);
	}

	util::window.setView(old_view);
}