#include "spitter.h"

#include "../../ingame.h"

#include <iostream>

Spitter::Spitter(in_game * ingame, sf::Vector2f position, float angle_deg, float atk_frequency_ms, float atk_speed, sf::Vector2f oprire)
	: ingame(ingame), frequency(144.0 * atk_frequency_ms / 1000.0), speed(atk_speed), punct_oprire(oprire),
	attacking_animation("samples/animations/spitter-attacking", &sprite) {

	//non_global_pos = sf::Vector2f(ingame->convert_to_local_space(position));
	non_global_pos = position;

	angle = angle_deg * PI / 180.0;

	direction = sf::Vector2f(std::cos(angle), std::sin(angle));
	direction *= atk_speed;
	
	position = ingame->convert_to_global_space(position);

	//direction = ingame->convert_to_global_space(direction);

	sprite.setPosition(position);
	sprite.setSize(ingame->convert_to_global_space({ 32, 16 }));

	move_state = idle;

	attacking_animation.reset();

	attack_frames_remaining = frequency;
}

bool Spitter::in_hitbox(sf::FloatRect& rect) {
	for (auto& i : bullets) {
		if (i.get_hb(ingame).intersects(rect) == 1) return 1;
	}
	return 0;
}

void Spitter::update() {
	accumulated += util::delta_time;
	while (accumulated >= 1) {
		update_once();
		accumulated -= 1;
	}
	
	attacking_animation.update();
	
}

float Spitter::dist(sf::Vector2f a, sf::Vector2f b) {
	return std::sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}

void Spitter::update_once() {
	for (int i = 0; i < bullets.size(); i++) {
		bullets[i].update();
		if (dist(bullets[i].current_position, punct_oprire) <= 1.1f) {
			bullets.erase(bullets.begin() + i);
			i--;
		}
	}

	attack_frames_remaining--;
	if (attack_frames_remaining <= 10 && spawned == 0) {
		spawn_new_bullet();
		spawned = 1;
	}
	if (attack_frames_remaining <= 0) {
		attack_frames_remaining = frequency;
		spawned = 0;
	}
}

void Spitter::draw() {
	for (auto& i : bullets) i.draw(ingame);
	util::window.draw(sprite);

	// hb
	/*
	for (auto& i : bullets) {
		sf::FloatRect rect = i.get_hb(ingame);
		sf::RectangleShape hb;
		hb.setSize(sf::Vector2f(rect.width, rect.height));
		hb.setPosition(sf::Vector2f(rect.left, rect.top));
		hb.setFillColor(sf::Color(0, 255, 0, 122));
		util::window.draw(hb);
	}
	*/
}

void Spitter::spawn_new_bullet() {
	bullets.push_back(*new bullet(non_global_pos + sf::Vector2f(16, 8), direction));
}

Spitter::bullet::bullet(sf::Vector2f position, sf::Vector2f direction) {
	sprite.setRadius(2.0f * 4);
	sprite.setFillColor(sf::Color::Red);

	current_velocity = direction;

	current_position = position;
}

void Spitter::bullet::update() {
	current_velocity = current_velocity * 9.975f / 10.0f;
	current_velocity.y += 0.005f;

	current_position += current_velocity;
}

sf::FloatRect Spitter::bullet::get_hb(in_game* ingame) {
	return sf::FloatRect(ingame->convert_to_global_space(sf::Vector2f(current_position)) + sf::Vector2f(2, 2), {12, 12});
}

void Spitter::bullet::draw(in_game * ingame) {
	sprite.setPosition(ingame->convert_to_global_space(current_position));
	util::window.draw(sprite);
}