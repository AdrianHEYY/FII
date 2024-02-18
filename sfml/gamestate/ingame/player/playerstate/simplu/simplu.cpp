#include "simplu.h"

Player_Simplu::Player_Simplu() {
	texture.loadFromFile("samples/player_simplu.png");
	sprite.setTexture(&texture);

	sprite.setSize(sf::Vector2f(100.0, 100.0));
}
void Player_Simplu::update() {

}