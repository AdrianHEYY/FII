#pragma once

#include "../enemy.h"
#include <chrono>

extern class in_game;

class Spike : public Enemy {
public:
	/// <summary>
	/// I apologise to the gods of cpp for creating a function with 9 arguments. I will repent for my sins. 
	/// </summary>
	/// <param name="start_pos">local space</param>
	/// <param name="windup_pos">local space</param>
	/// <param name="final_pos">local space</param>
	/// <param name="stay_start_time">in ms</param>
	/// <param name="stay_windup_time">in ms</param>
	/// <param name="stay_final_time">in ms</param>
	/// <param name="move_start_windup_time">in ms</param>
	/// <param name="move_windup_final_time">in ms</param>
	/// <param name="move_final_start_time">in ms</param>
	Spike(in_game* ingame, sf::Vector2f start_pos, sf::Vector2f windup_pos, sf::Vector2f final_pos, int stay_start_time, int stay_windup_time, int stay_final_time, int move_start_windup_time, int move_windup_final_time, int move_final_start_time);
	void update(float delta_time) override;
	void draw(sf::RenderWindow& win) override;
private:
	in_game* ingame;

	enum states {
		start_windup, windup_final, final_start,
		resting_start, resting_windup, resting_final
	};

	void update_once();

	sf::Texture texture;
	sf::RectangleShape sprite;
	states move_state;

	int cat_mai_am_de_stat = 0;

	sf::Vector2f start_pos, windup_pos, final_pos;
	sf::Vector2f start_windup_direction, windup_final_direction, final_start_direction;
	float stay_start_time, stay_windup_time, stay_final_time;
	float move_start_windup_time, move_windup_final_time, move_final_start_time;
};