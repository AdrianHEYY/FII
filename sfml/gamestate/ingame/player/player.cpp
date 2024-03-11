#include "player.h"
#include "../ingame.h"

player::player(in_game* game)
	: animation_walk("samples/animations/mc-walk", &sprite),
	animation_idle("samples/animations/mc-idle", &sprite) {
	ingame = game;

	//current_player = new Player_Simplu(this);
	velocity = sf::Vector2f(0.0f, 0.0f);

	// 8k 4k
	sf::Vector2f start_pos = sf::Vector2f(8000.0f, 4000.0f);

	off_position = sf::Vector2f(start_pos);
	sprite.setPosition(sf::Vector2f(start_pos));
	sf::View view = util::window.getView();
	view.move(sf::Vector2f(start_pos));
	util::window.setView(view);
	velocity = sf::Vector2f(0.0f, 0.0f);

	// il pun pe centru
	sprite.setPosition(start_pos + sf::Vector2f(util::window.getSize()) / 2.0f - sprite.getSize() / 2.0f);

	sprite.setSize(sf::Vector2f(32.0f * 4, 32.0f * 4));

	hitbox_size = sf::Vector2f(48.0 * 2 - 38, 64.0 * 2 - 16); // todo pune astea intr-un text file sau ceva ca nu prea merge aicea adica n-0i rau dar meh
	hitbox_sprite_offset = sf::Vector2f(35, 8);

	animation_idle.reset();
	animation_walk.reset();

}

void player::draw() {
	util::window.draw(sprite);

	// vvv hitbox vvv
	bool deb = 1;
	if (deb == 1) {
		sf::RectangleShape rect;
		sf::Vector2f oldPos = sprite.getPosition();
		rect.setPosition(hitbox_sprite_offset + oldPos);
		rect.setSize(hitbox_size);
		rect.setFillColor(sf::Color(0, 255, 0, 122));
		util::window.draw(rect);
	}
}

#include <iostream> //todo

void player::update() {
	sf::Vector2f pos = sprite.getPosition();
	sf::Vector2f old_velocity = velocity;
	//std::cout << pos.x << ' ' << pos.y << '\n';


	const float fixedTimeStep = 1.0f;

	static float accumulatedTime = 0.0f;
	accumulatedTime += util::delta_time;
	while (accumulatedTime >= fixedTimeStep) {
		update_movement();
		accumulatedTime -= fixedTimeStep;
	}


	// animatiile vvv
	if (velocity.y == 0) { // on ground (sau in aer un frame =) )
		if (velocity.x < 0) {
			animation_walk.mirror(1);
			animation_idle.mirror(1);
		}
		else if (velocity.x > 0) {
			animation_walk.mirror(0);
			animation_idle.mirror(0);
		}
		else {
			if (old_velocity.x < 0) {
				animation_walk.mirror(1);
				animation_idle.mirror(1);
			}
			else if (old_velocity.x > 0) {
				animation_walk.mirror(0);
				animation_idle.mirror(0);
			}
		}
		if (old_velocity.x == 0 && velocity.x != 0) { // am inceput sa ma misc
			animation_walk.reset();
			animation_walk.update(); // todo: cand ma misc in stanga, oglindeste asta, paramentru la fucntie or sum shit like that, posibil mica animatie de intoarcere? (nope)
		}
		else if (old_velocity.x != 0 && velocity.x != 0) { // ma misc in continuare
			animation_walk.update();
		}
		else if (old_velocity.x != 0 && velocity.x == 0) { // idle start
			animation_idle.reset();
			animation_idle.update();
		}
		else if (old_velocity.x == 0 && velocity.x == 0) { // idle continua
			animation_idle.update();
		}
	}
	else { // sunt in aer

	}
	// animatiile ^^^

}

#include <iostream> //todo

void player::update_movement_AD(sf::Vector2f &velocity) {
	if (util::keyboard::is_pressed(sf::Keyboard::A))
	{
		velocity.x -= 1.5; //todo 1.5 si 6 requires tweaking
		if (velocity.x < -6)
			velocity.x = -6;
	}
	if (util::keyboard::is_pressed(sf::Keyboard::D))
	{
		velocity.x += 1.5;
		if (velocity.x > 6)
			velocity.x = 6;
	}
	if (!util::keyboard::is_pressed(sf::Keyboard::A) && !util::keyboard::is_pressed(sf::Keyboard::D) && velocity.x != 0)
	{
		int oldX = velocity.x;
		velocity.x += ((velocity.x < 0) ? 1.0f : -1.0f);
		if ((oldX < 0 && velocity.x > 0) || (oldX > 0 && velocity.x < 0)) velocity.x = 0;
	}
}

bool player::can_go(sf::Vector2f new_pos, sf::Vector2f size) {
	sf::FloatRect rect = ingame->map_empty_rect(new_pos, size);
	if (rect.height != 0 && rect.width != 0) {
		return 0;
	}
	else {
		return 1;
	}
}

void player::update_movement() {
	//std::cout << sprite.getPosition().x << ' ' << sprite.getPosition().y << '\n';
	
	sf::View view = util::window.getView();

	sf::Vector2f velocity = this->velocity;
	sf::Vector2f old_velocity = velocity;

	sf::FloatRect current_hb = get_hitbox();
	sf::Vector2f current_pos(current_hb.left, current_hb.top);
	sf::Vector2f current_size(current_hb.width, current_hb.height);


	update_movement_AD(velocity);

	bool check_jump = 1;

	if (can_wall_grab && wall_grab == 1) { 
		check_jump = 0;
		if (util::keyboard::just_pressed(sf::Keyboard::Space)) {
			velocity.y = -11;

			velocity.x = 10 * ((wall_grab_direction == 0) ? 1 : -1);

			wall_grab = 0;
		}
		else if (util::keyboard::just_released(sf::Keyboard::Left)) {
			// m-am despartit
			wall_grab = 0;
			check_jump = 1;
		}
		else if (can_go(current_pos + velocity, current_size) == 1) {
			// m-am miscat de pe zid | (poate nu dau release la Left)
			bool ok = 0;
			if (wall_grab_direction == 0 && util::keyboard::is_pressed(sf::Keyboard::D)) ok = 1;
			if (wall_grab_direction == 1 && util::keyboard::is_pressed(sf::Keyboard::A)) ok = 1;
			
			if (ok == 1) {
				check_jump = 1;
				wall_grab = 0;
			}
			else {
				velocity.y += 0.01;
			}
		}
		else {
			// slide lejer 
			velocity.y += 0.01;
		}
	}

	static bool jumping = 0;
	if (check_jump == 1) {
		if (jumping == 0) {
			velocity.y += 1;
			if (velocity.y > 11) velocity.y = 11;

			sf::FloatRect rect_vel_y = ingame->map_empty_rect(current_pos + sf::Vector2f(0, velocity.y), current_size);
			if (rect_vel_y.height != 0 && rect_vel_y.width != 0) {
				// pe podea
				if (util::keyboard::just_pressed(sf::Keyboard::Key::Space)) {
					velocity.y = -11;
					jumping = 1;
				}
			}

		}
		else {
			velocity.y += 0.3;
			if (velocity.y > 0) velocity.y = 0, jumping = 0;
		}
	}

	bool on_ground = 0;
	bool near_wall = 0;

	// verificare zid la standa - dreapta
	sf::FloatRect rect_vel_x = ingame->map_empty_rect(current_pos + sf::Vector2f(velocity.x, 0), current_size);
	if (rect_vel_x.height != 0 && rect_vel_x.width != 0) {
		velocity.x = 0; 
		near_wall = 1;
	}
	// verificare zid jos - sus
	sf::FloatRect rect_vel_y = ingame->map_empty_rect(current_pos + sf::Vector2f(0, velocity.y), current_size);
	if (rect_vel_y.height != 0 && rect_vel_y.width != 0) {
		velocity.y = 0;
		jumping = 0;
		wall_grab = 0;
		if (rect_vel_y.top >= current_pos.y + current_size.y) on_ground = 1;
	}
	// verificare colturi in caz de ceva
	sf::FloatRect rect_vel_xy = ingame->map_empty_rect(current_pos + sf::Vector2f(velocity.x, velocity.y), current_size);
	if (rect_vel_xy.height != 0 && rect_vel_xy.width != 0) {
		velocity.x = 0; 
		velocity.y = 0;
	}


	if (can_wall_grab) {
		static std::chrono::high_resolution_clock::time_point left = std::chrono::high_resolution_clock::now();
		if (util::keyboard::just_pressed(sf::Keyboard::Left)) left = std::chrono::high_resolution_clock::now();
		bool close_enough_timing_left_key = 0;
		if (std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - left).count() <= 100) close_enough_timing_left_key = 1;
		if (on_ground == 0 && near_wall == 1 && close_enough_timing_left_key == 1 && rect_vel_x.width <= 10) { // wall grab
			velocity.y = 0;
			wall_grab = 1;
			jumping = 1;
			wall_grab_direction = (rect_vel_x.left + rect_vel_x.width <= current_pos.x) ? 0 : 1;
		}
	}

	sf::Vector2f delta_velocity = velocity;

	move(delta_velocity);

	sf::FloatRect rect_vel_final = ingame->map_empty_rect(get_hitbox());
	if (rect_vel_final.height != 0 && rect_vel_final.width != 0) { // in caz de ceva doar ma opresc 
		move(-delta_velocity);
		velocity = sf::Vector2f(0, 0); // sper din suflet ca ce fac aici merge bine
		return;
	}

	view.move(delta_velocity);
	this->velocity = velocity; // aici velocity, nu delta-velocity!
	this->velocity = velocity;
	off_position = off_position + delta_velocity;
	util::window.setView(view);
}