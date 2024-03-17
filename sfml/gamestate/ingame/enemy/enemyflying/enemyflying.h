#pragma once

#include "../enemy.h"
#include "../../../../animation/animation.h"

extern class in_game;

class Enemy_Flying : public Enemy {
public:
	/// <summary>
	/// 
	/// </summary>
	/// <param name="start_pos"></param>
	/// <param name="end_pos"></param>
	/// <param name="move_speed"></param>
	/// <param name="rest_time">in milliseconds</param>
	Enemy_Flying(in_game* ingame, sf::Vector2f start_pos, sf::Vector2f end_pos, float move_speed, float rest_time);

	void update() override;

	void draw() override;

	bool in_hitbox(sf::FloatRect& rect) override;
private:
	void update_once();

	Animation animation;

	in_game* ingame;

	enum states {
		stay_start, move_start_end, stay_end, move_end_start
	};
	states move_state = stay_start;

	sf::RectangleShape sprite;

	sf::Vector2f start_pos;
	sf::Vector2f end_pos;
	sf::Vector2f direction;
	float move_speed;
	float rest_time;
	float rest_timer = 0;
	float distance;
	bool resting;

	sf::Vector2f hitbox_off;
	sf::RectangleShape hitbox;
};