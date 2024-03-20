#pragma once 

#include "../enemy.h"
#include <SFML/Graphics.hpp>

extern class in_game;

class Void : public Enemy {
public:
	Void(in_game *ingame, sf::Vector2f position, sf::Vector2f size);
	void draw() override;
	bool in_hitbox(sf::FloatRect& rect) override;
private:
	in_game* ingame;

	sf::RectangleShape sprite;
	sf::Image im;
	sf::Texture tex;

	sf::Vector2f hitbox_off;
	sf::Vector2f hitbox_size;
};