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
		inamici
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
					float angle, freq, speed;
					in >> pos.x >> pos.y >> angle >> freq >> speed;
					pos = map.convert_to_global_space(pos);
					enemies.push_back(new Spitter(this, pos, angle, freq, speed));
					//std::cout << "Here\n";
				}
				if (input == "spike") {
					sf::Vector2f p1, p2, p3;
					float a, b, c, d, e, f;
					in >> p1.x >> p1.y >> p2.x >> p2.y >> p3.x >> p3.y >> a >> b >> c >> d >> e >> f;
					p1 = map.convert_to_global_space(p1);
					p2 = map.convert_to_global_space(p2);
					p3 = map.convert_to_global_space(p3);
					enemies.push_back(new Spike(this, p1, p2, p3, a, b, c, d, e, f));
				}
			}
			break;
			}
		}
	}
	in.close();
	// ^^^

}

void in_game::draw() 
{
	map.draw();
	for (auto& i : enemies) i->draw(util::window); // todo nu-l mai da ca parametru
	sprite.draw();
}

void in_game::update() 
{
	for (auto& i : enemies) i->update(1.0); // todo: vezi ca ai deja deltaltime in util
	sprite.update();
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
