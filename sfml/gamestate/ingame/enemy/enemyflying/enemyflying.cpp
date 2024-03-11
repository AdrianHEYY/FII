#include "enemyflying.h"

#include "../../ingame.h"

#include <iostream>

Enemy_Flying::Enemy_Flying(in_game* ingame, sf::Vector2f start_pos, sf::Vector2f end_pos, float move_speed, float rest_time)
	: ingame(ingame), start_pos(start_pos), end_pos(end_pos), move_speed(move_speed * 3), rest_time(rest_time * 144.0 / 1000.0), resting(false) ,
	animation("samples/animations/flying-enemy", &sprite) {
	sprite.setPosition(start_pos);
	sprite.setSize(ingame->convert_to_global_space({ 20, 16 }));

	distance = sqrt(pow(end_pos.x - start_pos.x, 2) + pow(end_pos.y - start_pos.y, 2));

	direction = (end_pos - start_pos) / distance;
	direction *= move_speed;

	//std::cout << direction.x << ' ' << direction.y << '\n';

	move_state = stay_start;

	animation.reset();
}

void Enemy_Flying::update(float deltaTime) {
	static float accumulated = 0;
	accumulated += deltaTime;
	while (accumulated >= 1) {
		update_once();
		accumulated -= 1;
	}
	animation.update();
}

void Enemy_Flying::update_once() {
	auto distance = [&](sf::Vector2f a, sf::Vector2f b) -> float {
		return std::sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
		};

	switch (move_state) {
	case stay_start:
		rest_timer++;
		if (rest_timer >= rest_time) move_state = move_start_end;
		break;
	case move_start_end:
		//std::cout << distance(sprite.getPosition(), end_pos) << '\n';
		sprite.setPosition(sprite.getPosition() + direction);
		if (distance(sprite.getPosition(), end_pos) < direction.x * direction.x + direction.y * direction.y) move_state = stay_end, rest_timer = 0, sprite.setPosition(end_pos);
		break;
	case stay_end:
		rest_timer++;
		if (rest_timer >= rest_time) move_state = move_end_start;
		break;
	case move_end_start:
		sprite.setPosition(sprite.getPosition() - direction);
		if (distance(sprite.getPosition(), start_pos) < direction.x * direction.x + direction.y * direction.y) move_state = stay_start, rest_timer = 0, sprite.setPosition(start_pos);
		break;
	default:
		break;
	}
}

//#include <iostream>
void Enemy_Flying::draw(sf::RenderWindow& window) {
	window.draw(sprite);
}