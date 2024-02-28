#include "simplu.h"

#include "../../../../../util/util.h"
#include "../../../../../util/keyboard/keyboard.h"
#include "../../player.h"
#include "././../../../ingame.h"

Player_Simplu::Player_Simplu(player * player_ptr) 
: animation_walk("samples/animations/mc-walk", &sprite) ,
  animation_idle("samples/animations/mc-idle", &sprite) {
	this->player_ptr = player_ptr;

	sprite.setSize(sf::Vector2f(32.0f * 4, 32.0f * 4));

	hitbox_size = sf::Vector2f(48.0 * 2 - 38, 64.0 * 2 - 16); // todo pune astea intr-un text file sau ceva ca nu prea merge aicea adica n-0i rau dar meh
	hitbox_sprite_offset = sf::Vector2f(40, 8);

	animation_idle.reset();
	animation_walk.reset();
}

void Player_Simplu::update() {
	const float fixedTimeStep = 1.0f; 

	static float accumulatedTime = 0.0f;
	accumulatedTime += util::delta_time;
	while (accumulatedTime >= fixedTimeStep) { 
		update_movement(); 
		accumulatedTime -= fixedTimeStep;
	}
}
void Player_Simplu::update_movement() {
	sf::View view = util::window.getView();

	sf::Vector2f velocity = player_ptr->getVelocity();
	sf::Vector2f old_velocity = velocity;

	in_game* ingame = player_ptr->getIngame();

	if (util::keyboard::is_pressed(sf::Keyboard::A))
	{
		velocity.x-= 1.5; //todo 1.5 si 6 requires tweaking
		if (velocity.x < -6)
			velocity.x = -6;
	}
	if (util::keyboard::is_pressed(sf::Keyboard::D))
	{
		velocity.x+= 1.5;
		if (velocity.x > 6)
			velocity.x = 6;
	}
	if (!util::keyboard::is_pressed(sf::Keyboard::A) && !util::keyboard::is_pressed(sf::Keyboard::D) && velocity.x != 0)
	{
		int oldX = velocity.x;
		velocity.x += ((velocity.x < 0) ? 1.0f : -1.0f);
		if ((oldX < 0 && velocity.x > 0) || (oldX > 0 && velocity.x < 0)) velocity.x = 0;
	}

	sf::FloatRect current_hb = get_hitbox();

	sf::Vector2f current_pos(current_hb.left, current_hb.top);
	sf::Vector2f current_size(current_hb.width, current_hb.height);

	sf::FloatRect rect_vel_x = ingame->map_empty_rect(current_pos + velocity, current_size);
	if (rect_vel_x.height != 0 && rect_vel_x.width != 0) {
		velocity.x = 0; // todo seteaza pozitia noua fix langa perete
	}

	static bool jumping = 0;

	if (jumping == 0) {
		velocity.y += 1;
		if (velocity.y > 11) velocity.y = 11;

		sf::FloatRect rect_vel_y = ingame->map_empty_rect(current_pos + sf::Vector2f(0, velocity.y), current_size);
		if (rect_vel_y.height != 0 && rect_vel_y.width != 0) { // todo podea, lipeste sprite-ul
			velocity.y = 0; // pe pamant
			if (util::keyboard::just_pressed(sf::Keyboard::Key::Space)) {
				velocity.y -= 11;
				jumping = 1;
			}
		}

	}
	else {
		velocity.y += 0.3;
		if (velocity.y > 0) velocity.y = 0, jumping = 0;

		sf::FloatRect rect_vel_y = ingame->map_empty_rect(current_pos + sf::Vector2f(0, velocity.y), current_size);
		if (velocity.y < 0 && rect_vel_y.height != 0 && rect_vel_y.width != 0) { // todo tavan, la fel
			velocity.y = 0;
			jumping = 0;
		}
	}

	// animatiile vvv
	if (velocity.y == 0) {
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
	// animatiile ^^^

	sf::Vector2f delta_velocity = velocity;

	move(delta_velocity);

	sf::FloatRect rect_vel_y = ingame->map_empty_rect(get_hitbox());
	if (rect_vel_y.height != 0 && rect_vel_y.width != 0) { // in caz de ceva doar ma opresc 
		move(-delta_velocity);
		player_ptr->setVelocity({ 0, 0 }); // sper din suflet ca ce fac aici merge bine
		return;
	}

	view.move(delta_velocity);
	player_ptr->setVelocity(velocity); // aici velocity, nu delta-velocity!
	player_ptr->setOffPosition(player_ptr->getOffPosition() + delta_velocity);
	util::window.setView(view);
}