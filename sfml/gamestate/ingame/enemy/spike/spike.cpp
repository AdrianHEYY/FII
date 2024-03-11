#include "spike.h"

#include "../../map/map.h"
#include "../../ingame.h"
#include "../../../../util/util.h"
#include <math.h>

Spike::Spike(in_game* ingame, sf::Vector2f start_pos, sf::Vector2f windup_pos, sf::Vector2f final_pos, int stay_start_time, int stay_windup_time, int stay_final_time, int move_start_windup_time, int move_windup_final_time, int move_final_start_time)
	: ingame(ingame), start_pos(start_pos), windup_pos(windup_pos), final_pos(final_pos),
	stay_start_time(util::convert_ms_to_frames(stay_start_time)), stay_windup_time(util::convert_ms_to_frames(stay_windup_time)), stay_final_time(util::convert_ms_to_frames(stay_final_time)),
	move_start_windup_time(util::convert_ms_to_frames(move_start_windup_time)), move_windup_final_time(util::convert_ms_to_frames(move_windup_final_time)), move_final_start_time(util::convert_ms_to_frames(move_final_start_time)) {
	start_windup_direction = (windup_pos - start_pos) / this->move_start_windup_time;
	windup_final_direction = (final_pos - windup_pos) / this->move_windup_final_time;
	final_start_direction = (start_pos - final_pos) / this->move_final_start_time;

	sprite.setPosition(this->start_pos);
	sprite.setSize({ ingame->convert_to_global_space({64, 16}) });
	//sprite.setFillColor(sf::Color::Red);

	move_state = resting_start;
	cat_mai_am_de_stat = this->stay_start_time;

	texture.loadFromFile("samples/pointy-arrow.png");
	sprite.setTexture(&texture);
}
void Spike::update(float delta_time) {
	static float accumulated = 0;
	accumulated += delta_time;
	while (accumulated >= 1.0) {
		update_once();
		accumulated -= 1.0;
	}
}

void Spike::update_once() {
	sf::Vector2f position = sprite.getPosition();

	auto distance = [&](sf::Vector2f a, sf::Vector2f b) -> float {
		return std::sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
		};

	switch (move_state) {
	case resting_start:
		cat_mai_am_de_stat--;
		if (cat_mai_am_de_stat <= 0) move_state = start_windup;
		break;
	case resting_windup:
		cat_mai_am_de_stat--;
		if (cat_mai_am_de_stat <= 0) move_state = windup_final;
		break;
	case resting_final:
		cat_mai_am_de_stat--;
		if (cat_mai_am_de_stat <= 0) move_state = final_start;
		break;
	case start_windup:
		position += start_windup_direction;
		if (distance(position, windup_pos) < start_windup_direction.x * start_windup_direction.x + start_windup_direction.y * start_windup_direction.y) position = windup_pos, move_state = resting_windup, cat_mai_am_de_stat = stay_windup_time;
		break;
	case windup_final:
		position += windup_final_direction;
		if (distance(position, final_pos) < windup_final_direction.x * windup_final_direction.x + windup_final_direction.y * windup_final_direction.y) position = final_pos, move_state = resting_final, cat_mai_am_de_stat = stay_final_time;
		break;
	case final_start:
		position += final_start_direction;
		if (distance(position, start_pos) < final_start_direction.x * final_start_direction.x + final_start_direction.y * final_start_direction.y) position = start_pos, move_state = resting_start, cat_mai_am_de_stat = stay_start_time;
		break;
	default:
		throw std::runtime_error("Nu ar trb sa ajungi aici ce cati aici?");
		break;
	}
	sprite.setPosition(position);
}
void Spike::draw(sf::RenderWindow& win) {
	win.draw(sprite);
}