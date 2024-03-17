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
	Spitter(in_game * ingame, sf::Vector2f position, float angle_deg, float atk_frequency_ms, float atk_speed, sf::Vector2f oprire);
	void update() override;

	bool in_hitbox(sf::FloatRect& rect) override;

	void update_once();
	void draw() override;
private:
	float dist(sf::Vector2f a, sf::Vector2f b);
	void spawn_new_bullet();

	sf::Vector2f non_global_pos;

	float attack_frames_remaining;

	bool spawned = 0;
	float accumulated = 0;

	in_game* ingame;

	sf::RectangleShape sprite;
	sf::Vector2f position;
	Animation attacking_animation;

	sf::Vector2f punct_oprire = { -1, -1 };

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
		sf::FloatRect get_hb(in_game* ingame);
		void draw(in_game* ingame);
	};
	std::vector<bullet> bullets;

	
};