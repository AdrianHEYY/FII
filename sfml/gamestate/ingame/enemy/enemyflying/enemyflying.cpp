#include "enemyflying.h"

Enemy_Flying::Enemy_Flying(sf::Vector2f start_pos, sf::Vector2f end_pos, float move_speed, float rest_time)
	: start_pos(start_pos), end_pos(end_pos), move_speed(move_speed), rest_time(rest_time), resting(false) {
	sprite.setPosition(start_pos);
	sprite.setSize({ 20, 20 });
	sprite.setFillColor(sf::Color::Red);
	distance = sqrt(pow(end_pos.x - start_pos.x, 2) + pow(end_pos.y - start_pos.y, 2));
	direction = (end_pos - start_pos) / distance;
	cur_pos = start_pos;
}

void Enemy_Flying::update(float deltaTime) {
	static float accumulated = 0;
	accumulated += deltaTime;
	if (accumulated >= 1) {
		update_once();
		accumulated -= 1;
	}
}
void Enemy_Flying::update_once() {
	if (resting == 1) {
		rest_timer++;
		if (rest_timer > rest_time) {
			resting = 0;
			direction = -direction;
			cur_pos += direction;
		}
	}
	else {
		cur_pos += direction * move_speed;
		distance = sqrt(pow(cur_pos.x - end_pos.x, 2) + pow(cur_pos.y - end_pos.y, 2));
		if (distance < 0.99) {
			cur_pos = end_pos;
			resting = 1;
			rest_timer = 0;
		}
		else {
			distance = sqrt(pow(cur_pos.x - start_pos.x, 2) + pow(cur_pos.y - start_pos.y, 2));
			if (distance < 0.99) {
				cur_pos = start_pos;
				resting = 1;
				rest_timer = 0;
			}
		}
	}

}
#include <iostream>
void Enemy_Flying::draw(sf::RenderWindow& window) {
	sprite.setPosition(cur_pos);
	std::cout << cur_pos.x << ' ' << cur_pos.y << '\n';
	window.draw(sprite);
}