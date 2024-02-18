#include "player.h"
#include "../ingame.h"

#include "playerstate/simplu/simplu.h"

player::player(in_game* game) {
	current_player = new Player_Simplu();
	velocity = sf::Vector2f(0.0f, 0.0f);

	current_player->get_sprite().setPosition(sf::Vector2f(util::window.getSize()) / 2.0f - current_player->get_sprite().getSize() / 2.0f);
	
}

void player::draw() {
	current_player->draw();
}

void player::update() {

	if (util::keyboard::is_pressed(sf::Keyboard::A))
	{
		velocity.x--;
		if (velocity.x < -3)
			velocity.x = -3;
	}
	if (util::keyboard::is_pressed(sf::Keyboard::D))
	{
		velocity.x++;
		if (velocity.x > 3)
			velocity.x = 3;
	}
	static bool jumping = 0;
	
	if (util::keyboard::is_pressed(sf::Keyboard::Key::Space))
	{
		jumping = 1;
		velocity.y--;
		if (velocity.y < -3)
			velocity.y = -3;
	}
	else {
		if (jumping == 1 && velocity.y != 0) velocity.y += ((velocity.y < 0) ? 1.0f : -1.0f);
	}
	
	if (util::keyboard::is_pressed(sf::Keyboard::S))
	{
		velocity.y++;
		if (velocity.y > 3)
			velocity.y = 3;
	}
	if (!util::keyboard::is_pressed(sf::Keyboard::A) && !util::keyboard::is_pressed(sf::Keyboard::D) && velocity.x != 0)
	{
		velocity.x += ((velocity.x < 0) ? 1.0f : -1.0f);
	}


	float distance = std::sqrt(std::pow(velocity.x, 2) + std::pow(velocity.y, 2));
	distance += (distance == 0);
	sf::Vector2f normalize = velocity/distance;
	normalize *= 3.0f;


	sf::Vector2f current_pos = current_player->get_sprite().getPosition();
	current_player->get_sprite().setPosition(current_pos + normalize);

}