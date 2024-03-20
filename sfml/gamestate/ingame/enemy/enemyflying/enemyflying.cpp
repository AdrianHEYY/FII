#include "enemyflying.h"

#include "../../ingame.h"
#include "../../../../util/util.h"
#include "../../../../util/shaders/shaders.h"

Enemy_Flying::Enemy_Flying(in_game* ingame, sf::Vector2f start_pos, sf::Vector2f end_pos, float move_speed, float rest_time)
	: ingame(ingame), start_pos(start_pos), end_pos(end_pos), move_speed(move_speed * 3), rest_time(rest_time * 144.0 / 1000.0), resting(false) ,
	animation("samples/animations/flying-enemy", &sprite) {
	sprite.setPosition(start_pos);
	sprite.setSize(ingame->convert_to_global_space({ 20, 16 }));

	move_speed *= 3;

	distance = sqrt(pow(end_pos.x - start_pos.x, 2) + pow(end_pos.y - start_pos.y, 2));

	direction = (end_pos - start_pos) / distance;
	direction *= move_speed;

	move_state = stay_start;

	animation.reset();


	hitbox.setSize(ingame->convert_to_global_space({ 16, 12 }));
	hitbox.setFillColor(sf::Color(255, 0, 0, 122));
	hitbox_off = sf::Vector2f({ 8, 6 });
}

bool Enemy_Flying::in_hitbox(sf::FloatRect&rect) {
	if (hitbox.getGlobalBounds().intersects(rect)) return 1;
	return 0;
}

void Enemy_Flying::update() {
	static float accumulated = 0;
	accumulated += util::delta_time;
	while (accumulated >= 1) {
		update_once();
		accumulated -= 1;
	}
	if (move_state == move_start_end || move_state == stay_start) {
		animation.mirror(true);
	}
	else {
		animation.mirror(false);
	}
	animation.update();

	hitbox.setPosition(sprite.getPosition() + hitbox_off);
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

void Enemy_Flying::draw() {
	util::window.draw(sprite, &util::shaders::vignette);

	//window.draw(hitbox);
}