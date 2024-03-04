#pragma once

#include "../enemy.h"

class Enemy_Flying : public Enemy {
public:
	/// <summary>
	/// 
	/// </summary>
	/// <param name="start_pos"></param>
	/// <param name="end_pos"></param>
	/// <param name="move_speed"></param>
	/// <param name="rest_time">in frames(144 = 1 second)</param>
	Enemy_Flying(sf::Vector2f start_pos, sf::Vector2f end_pos, float move_speed, float rest_time);

	void update(float delta_time);

	void draw(sf::RenderWindow& window) override;
private:
	void update_once();

	sf::RectangleShape sprite;

	sf::Vector2f start_pos;
	sf::Vector2f end_pos;
	sf::Vector2f cur_pos;
	sf::Vector2f direction;
	float move_speed;
	float rest_time;
	float rest_timer = 0;
	float distance;
	bool resting;
};