#include "spitter.h"

#include "../../ingame.h"

Spitter::Spitter(in_game * ingame, sf::Vector2f position, float angle_deg, float atk_frequency_ms, float atk_speed)
	: ingame(ingame), position(position), angle(angle_deg), frequency(144.0 * atk_frequency_ms / 1000.0), speed(atk_speed),
	idle_a("samples/animations/spitter-idle", &sprite),
	attacking_animation("samples/animations/spitter-attacking", &sprite) {

	angle = angle_deg * PI / 180.0;
	direction = sf::Vector2f(std::cos(angle), std::sin(angle));
	//direction = ingame->convert_to_global_space(direction); // un multiplier micutz
	direction = direction * 3.0f;
	direction *= atk_speed;

	sprite.setPosition(position);
	sprite.setSize(ingame->convert_to_global_space({ 32, 16 }));

	move_state = idle;

	attacking_animation.reset();
}

void Spitter::update(float delta_time) {
	static float accumulated = 0;
	accumulated += delta_time;
	while (accumulated >= 1) {
		update_once();
		accumulated -= 1;
	}
	switch (move_state) {
	case idle:
		idle_a.update();
		break;
	case attacking:
		attacking_animation.update();
		break;
	default:
		break;
	}
}

void Spitter::update_once() {
	for (auto& i : bullets) i.update();

	static int attack_frames_remaining = 144;
	switch (move_state) {
	case idle:
		time_remaining_idle--;
		if (time_remaining_idle <= 0) {
			move_state = attacking;
			attacking_animation.reset();
			attack_frames_remaining = 144;
		}
		break;
	case attacking:
		attack_frames_remaining--;
		if (attack_frames_remaining <= 0) {
			move_state = idle;
			time_remaining_idle = frequency;
			idle_a.reset();
		}
		if (attack_frames_remaining == 10) {
			spawn_new_bullet();
		}
		break;
	}
}

void Spitter::draw(sf::RenderWindow& win) {
	for (auto& i : bullets) i.draw(win);
	win.draw(sprite);
}

void Spitter::spawn_new_bullet() {
	bullets.push_back(*new bullet(position + sprite.getSize() / 2.0f, direction));
}

Spitter::bullet::bullet(sf::Vector2f position, sf::Vector2f direction) {
	sprite.setRadius(2.0f * 4);
	sprite.setFillColor(sf::Color::Red);

	current_velocity = direction;

	current_position = position;
}

void Spitter::bullet::update() {
	current_velocity.x = current_velocity.x * 9.975 / 10.0;
	current_velocity.y += 0.005f;

	current_position += current_velocity;
}

void Spitter::bullet::draw(sf::RenderWindow& win) {
	sprite.setPosition(current_position);
	win.draw(sprite);
}