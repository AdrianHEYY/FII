#include "ingame.h"

in_game::in_game(Game* game) 
	:sprite(this)
{
	this->game = game;
}

void in_game::draw() 
{
	map.draw();
	sprite.draw();
}

void in_game::update() 
{
	sprite.update();
}