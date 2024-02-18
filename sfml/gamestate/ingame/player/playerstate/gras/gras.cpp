#include "gras.h"

Player_Gras::Player_Gras() {
	texture.loadFromFile("samples/player_gras.png");
	sprite.setTexture(&texture);

	sprite.setSize(sf::Vector2f(100.0, 100.0));
}

void Player_Gras::update() {

}