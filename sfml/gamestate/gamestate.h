#pragma once

#include <SFML/Graphics.hpp>
#include "../util/keyboard/keyboard.h"
#include "../util/mouse/mouse.h"
#include "../util/util.h"

enum game_states
{
	NONE, 
	MAIN_MENU,
	IN_GAME,
	OPTIONS
};

extern class Game;

class game_state
{
public:
	virtual void draw();
	virtual void update();
protected:
	Game* game;
};