#include "ingame.h"

#include <fstream>
#include <string>

#include "../../game/game.h"

in_game::in_game(Game* game) 
	:sprite(this)
{
	this->game = game;

	// loading things:
	enum etape {
		hitbox,
		inamici,
		npcuri
	};
	std::string input;
	std::ifstream in;
	in.open("samples/mapa_finala.txt");
	etape etapa_cur;
	while (in >> input) {
		if (input == "HITBOX") {
			etapa_cur = hitbox;
		}
		else if (input == "INAMICI") {
			etapa_cur = inamici;
		}
		else if (input == "NPC") {
			etapa_cur = npcuri;
		}
		else {
			switch (etapa_cur) {
			case hitbox:
			{
				int unu = std::stoi(input);
				int doi, trei, patru;
				in >> doi >> trei >> patru;
				map.add_wall_collision(unu, doi, trei, patru);
			}
				break;
			case inamici:
			{
				if (input == "flying") {
					sf::Vector2f st_pos, end_pos;
					float speed, rest_time;
					in >> st_pos.x >> st_pos.y >> end_pos.x >> end_pos.y >> speed >> rest_time;
					st_pos = map.convert_to_global_space(st_pos);
					end_pos = map.convert_to_global_space(end_pos);
					Enemy_Flying* new_e = new Enemy_Flying(this, st_pos, end_pos, speed, rest_time);
					enemies.push_back(new_e);
				}
				if (input == "spitter") {
					sf::Vector2f pos;
					sf::Vector2f oprire;
					float angle, freq, speed;
					in >> pos.x >> pos.y >> angle >> freq >> speed >> oprire.x >> oprire.y;
					pos = pos;
					oprire = oprire;
					enemies.push_back(new Spitter(this, pos, angle, freq, speed, oprire));
				}
				if (input == "spike") {
					sf::Vector2f p1, p2, p3;
					float a, b, c, d, e, f;
					char direction;
					in >> p1.x >> p1.y >> p2.x >> p2.y >> p3.x >> p3.y >> a >> b >> c >> d >> e >> f >> direction;
					p1 = map.convert_to_global_space(p1);
					p2 = map.convert_to_global_space(p2);
					p3 = map.convert_to_global_space(p3);
					enemies.push_back(new Spike(this, p1, p2, p3, a, b, c, d, e, f, direction));
				}
				if (input == "void") {
					sf::Vector2f p, s;
					in >> p.x >> p.y >> s.x >> s.y;
					p = map.convert_to_global_space(p);
					s = map.convert_to_global_space(s);
					enemies.push_back(new Void(this, p, s));
				}
			}
				break;
			case npcuri: {
				sf::Vector2f position, size;

				// primul = wall_jump
				in >> position.y >> size.x >> size.y;
				position.x = std::stof(input);
				position = map.convert_to_global_space(position);
				size = map.convert_to_global_space(size);
				npcs[0] = new npc(this, "samples/animations/npc/wall_jump", "samples/texts/npc-wall-jump.txt", position, size);
				
				// doi = big_jump
				in >> position.x >> position.y >> size.x >> size.y;
				position = map.convert_to_global_space(position);
				size = map.convert_to_global_space(size);
				npcs[1] = new npc(this, "samples/animations/npc/big_jump", "samples/texts/npc-big-jump.txt", position, size);

				// trei = crouch
				in >> position.x >> position.y >> size.x >> size.y;
				position = map.convert_to_global_space(position);
				size = map.convert_to_global_space(size);
				npcs[2] = new npc(this, "samples/animations/npc/crouch", "samples/texts/npc-crouch.txt", position, size);

				// patru = dash
				in >> position.x >> position.y >> size.x >> size.y;
				position = map.convert_to_global_space(position);
				size = map.convert_to_global_space(size);
				npcs[3] = new npc(this, "samples/animations/npc/dash", "samples/texts/npc-dash.txt", position, size);

			}
				break;
			default:
				break;
			}
		}
	}
	in.close();
	// ^^^

	in.open("save.txt");
	if (!in.is_open()) {
		return;
	}
	int npc, a, b, c, d;
	in >> npc >> a >> b >> c >> d;
	current_save_file.last_npc_visited = npc;
	current_save_file.can_wall_jump = a;
	current_save_file.can_big_jump = b;
 	current_save_file.can_dash = d;
	if (a == 1) sprite.unlock_wall_jump();
	if (b == 1) sprite.unlock_big_jump();
	if (c == 1) sprite.unlock_crouch();
	if (d == 1) sprite.unlock_dash();
	respawn_player();
	in.close();


	big_red_button_texture.loadFromFile("samples/big-red-button.png");
	big_red_button_sprite.setTexture(&big_red_button_texture);
	big_red_button_sprite.setSize(convert_to_global_space(sf::Vector2f(36, 48)));
	big_red_button_sprite.setPosition({ 5800, 3390 });
}

void in_game::respawn_player() {
	int no_npc = current_save_file.last_npc_visited;

	sf::Vector2f loc;
	switch (no_npc) {
	case 0:
		loc = npcs[0]->get_pos() + sf::Vector2f(0, -70);
		break;
	case 1:
		loc = npcs[1]->get_pos() + sf::Vector2f(-200, -50);
		break;
	case 2:
		loc = npcs[2]->get_pos() + sf::Vector2f(-100, 20);
		break;
	case 3:
		loc = npcs[3]->get_pos() + sf::Vector2f(-200, -60);
		break;
	default:
		loc = sf::Vector2f(8000.0f, 5100.0f);
		break;
	};
	sprite.respawn_go_location(loc);
}

void in_game::draw() 
{
	if (util::big_done == 1) {
		// in caz ca vede cineva aceasta bucata de cod unholy, I'm sorry ok? e 12 si sunt pe 100mg de cafeina...
		sf::Texture tex;
		map.draw();
		for (auto& i : enemies) i->draw();
		for (int i = 0; i < 4; i++) {
			if (npcs[i] != nullptr) npcs[i]->draw();
		}
		util::window.draw(big_red_button_sprite);
		util::window.display();
		tex = util::window.getTexture();
		sf::Sprite spr;
		spr.setTexture(tex);
		sf::Shader sh;
		sf::Vector2f old_pos = sprite.getOffPosition();
		spr.setPosition(old_pos);
		sh.loadFromFile("shaders/big_done.vert", "shaders/big_done.frag");
		sh.setUniform("iResolution", sf::Vector2f(1920, 1080));
		sh.setUniform("texture", tex);
		std::chrono::time_point inc = std::chrono::high_resolution_clock::now();

		const int no_texts = 5;
		sf::Vector2f ws = sf::Vector2f(1920, 1080);
		sf::Text texts[no_texts];
		texts[0].setPosition(sf::Vector2f(ws.x / 2.0, -100));
		texts[0].setCharacterSize(40);
		texts[0].setFont(util::font);
		texts[0].setFillColor(sf::Color::Black);
		for (int i = 1; i < no_texts; i++) {
			texts[i].setPosition(texts[i - 1].getPosition() + sf::Vector2f(0, -200.0f));
			texts[i].setCharacterSize(texts[i - 1].getCharacterSize());
			texts[i].setFont(util::font);
			texts[i].setFillColor(sf::Color::Black);
		}
		texts[0].setString("A short game made by Adrian\n(for the FIICode GameJam)");
		texts[1].setString("Thanks a lot for playing");
		texts[2].setString("This whole thing took about 2 weeks of work");
		texts[3].setString(" ");
		texts[4].setString("Puteam sa adaug mult mai multe, dar am ramas fara timp :)");

		for (int i = 0; i < no_texts; i++) {
			float width = texts[i].getGlobalBounds().width;
			texts[i].setPosition(sf::Vector2f(texts[i].getPosition().x - width / 2.0f, texts[i].getPosition().y));
		}

		while (true) {
			long long trecut = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now()-inc).count();
			float sec_trecut = float(trecut) / 1000.0f;
			sh.setUniform("time", sec_trecut);

			util::renderwindow.clear();
			util::window.clear();

			util::window.draw(spr, &sh);
			
			sprite.draw();
			util::window.display();
			sf::Texture player_t = util::window.getTexture();
			sf::Sprite player_s;
			player_s.setTexture(player_t);

			util::renderwindow.draw(player_s);

			if (sec_trecut > 2.5) {
				float move_speed = 0.2;
				sprite.move_unsafe(sf::Vector2f({ 0,move_speed }));
				for (int i = 0; i < no_texts; i++) {
					texts[i].setPosition(texts[i].getPosition() + sf::Vector2f(0.0, move_speed * 0.8));
					util::renderwindow.draw(texts[i]);
				}
			}
			if (sec_trecut >= 16.0) {
				util::big_done = 0;
				game->setGameState(MAIN_MENU);
				break;
			}

			util::renderwindow.display();
		}
		return;
	}

	map.draw();
	for (auto& i : enemies) i->draw(); 
	for (int i = 0; i < 4; i++) {
		if (npcs[i] != nullptr) npcs[i]->draw();
	}
	util::window.draw(big_red_button_sprite);
	sprite.draw();

	
	/*sf::Vector2i pixelPos = sf::Mouse::getPosition(util::renderwindow);
	sf::Vector2f worldPos = util::window.mapPixelToCoords(pixelPos);
	sf::Vector2u pos_1 = map.convert_to_local_space(worldPos);

	sf::Text t;
	t.setFont(util::font);
	t.setPosition(sprite.getOffPosition());
	t.setCharacterSize(40);
	t.setFillColor(sf::Color::Red);
	t.setString("Mouse: " + std::to_string(worldPos.x) + " " + std::to_string(worldPos.y));
	util::window.draw(t);*/
	
}

void in_game::update() 
{
	if (util::big_done == 1) {
		return;
	}
	
	auto distance = [&](sf::Vector2f a, sf::Vector2f b) -> float {
		return std::sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
	};

	for (auto& i : enemies) i->update(); 
	sprite.update();

	for (int i = 0; i < 4; i++) {
		if (npcs[i] != nullptr) {
			if (distance(npcs[i]->get_pos(), sprite.getPosition() + sprite.getSize() / 2.0f) <= 150) {
				npcs[i]->show_dialogue_box(); 
				npcs[i]->progress_dialogue(); 
				current_save_file.last_npc_visited = i;
			}
			else {
				npcs[i]->close_dialogue_box();
			}

			if (npcs[i]->done()) {
				switch (i) {
				case 0:
					sprite.unlock_wall_jump();
					break;
				case 1:
					sprite.unlock_big_jump();
					break;
				case 2:
					sprite.unlock_crouch();
					break;
				case 3:
					sprite.unlock_dash();
					break;
				default:
					throw std::runtime_error("you shouldn't be here lmao");
					break;
				}
			}
		}
	}

	map.update(sprite.getOffPosition());

	if (util::keyboard::just_pressed(sf::Keyboard::Escape)) {
		game->setGameState(OPTIONS);
	};


	if (big_red_button_sprite.getGlobalBounds().intersects(sprite.get_hitbox()) == 1 && util::keyboard::just_pressed(sf::Keyboard::E)) {
		util::big_done = 1;
	}
}

sf::FloatRect in_game::map_empty_rect(sf::Vector2f poz_map, sf::Vector2f size) {
	return map.intersects_walls(sf::FloatRect(poz_map, size));
}

sf::FloatRect in_game::map_empty_rect(sf::FloatRect rect) {
	sf::Vector2f poz_map(rect.left, rect.top);
	sf::Vector2f size(rect.width, rect.height);
	return map_empty_rect(poz_map, size);
}

void in_game::save_last_npc(int new_npc) {
	current_save_file.last_npc_visited = new_npc;
}
void in_game::save_player_can_wall_jump() {
	current_save_file.can_wall_jump = 1;
}
void in_game::save_player_can_big_jump() {
	current_save_file.can_big_jump = 1;
}
void in_game::save_player_can_dash() {
	current_save_file.can_dash = 1;
}
void in_game::save_player_can_crouch() {
	current_save_file.can_crouch = 1;
}
in_game::~in_game() {
	std::ofstream save;
	save.open("save.txt");
	if (!save.is_open()) {
		return;
	}
	save << current_save_file.last_npc_visited << ' ' << current_save_file.can_wall_jump << ' ' << current_save_file.can_big_jump << ' ' << current_save_file.can_crouch << ' ' << current_save_file.can_dash << '\n';
	save.close();
}