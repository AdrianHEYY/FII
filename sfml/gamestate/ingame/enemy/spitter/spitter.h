#pragma once

#include "../enemy.h"

#include "../../../../animation/animation.h"

extern class in_game;

class Spitter : public Enemy {
public:
	/// <summary>
	/// vezi ca angle-ul este asa
	///      270
	///  180     0
	///       90
	/// </summary>
	Spitter(in_game * ingame, sf::Vector2f position, float angle_deg, float atk_frequency_ms, float atk_speed);
	void update(float delta_time) override;

	float time_remaining_idle = frequency;
	void update_once();
	void draw(sf::RenderWindow& win) override;
private:
	void spawn_new_bullet();

	in_game* ingame;

	sf::RectangleShape sprite;
	sf::Vector2f position;
	Animation attacking_animation;
	Animation idle_a;

	float speed; // projectile speed
	float angle; // projectile base angle
	sf::Vector2f direction;

	float frequency;

	const float PI = 3.14159265358979323846;

	enum states {
		idle, attacking
	};
	states move_state;

	sf::Texture bullet_texture;
	class bullet {
	public:
		sf::CircleShape sprite;
		sf::Vector2f current_velocity;
		sf::Vector2f current_position;
		bullet(sf::Vector2f position, sf::Vector2f direction);
		void update();
		void draw(sf::RenderWindow& win);
	};
	std::vector<bullet> bullets;

};