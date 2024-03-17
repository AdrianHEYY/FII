#include "ingame.h"

#include <fstream>
#include <string>
#include <iostream> //todo

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
	map.draw();
	for (auto& i : enemies) i->draw(); // todo nu-l mai da ca parametru
	for (int i = 0; i < 4; i++) {
		if (npcs[i] != nullptr) npcs[i]->draw();
	}
	sprite.draw();

	
	sf::Vector2i pixelPos = sf::Mouse::getPosition(util::renderwindow);
	sf::Vector2f worldPos = util::window.mapPixelToCoords(pixelPos);
	sf::Vector2u pos_1 = map.convert_to_local_space(worldPos);
	//std::cout << pos_1.x << ' ' << pos_1.y << '\n';

	//sf::CircleShape cs;
	//cs.setPosition(map.convert_to_global_space(sf::Vector2f(pos_1)));
	//cs.setRadius(7);
	//cs.setFillColor(sf::Color::Blue);
	//util::window.draw(cs);

	sf::Text t;
	t.setFont(util::font);
	t.setPosition(sprite.getOffPosition());
	t.setCharacterSize(40);
	t.setFillColor(sf::Color::Red);
	t.setString("Mouse: " + std::to_string(worldPos.x) + " " + std::to_string(worldPos.y));
	//util::window.draw(t);
	//util::window.display();
	
}
#include <iostream>
void in_game::update() 
{
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
}

sf::FloatRect in_game::map_empty_rect(sf::Vector2f poz_map, sf::Vector2f size) {
	//if (!map.can_go(poz_map)) return 0;
	//if (!map.can_go(poz_map + sf::Vector2f(size.x, 0))) return 0;
	//if (!map.can_go(poz_map + sf::Vector2f(0, size.y))) return 0;
	//if (!map.can_go(poz_map + size)) return 0;
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