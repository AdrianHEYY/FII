#include "furios.h"

Player_Furios::Player_Furios() {
	texture.loadFromFile("samples/player_furios.png");
	sprite.setTexture(&texture);

	sprite.setSize(sf::Vector2f(100.0, 100.0));
}

void Player_Furios::update() {

};