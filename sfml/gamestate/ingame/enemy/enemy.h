#pragma once

#include <SFML/Graphics.hpp>
#include <fstream>
#include "../../../util/util.h"

class Enemy {
public:
	Enemy();
	virtual void update();
	virtual void draw();
	virtual void save_file(std::ofstream& stream);
	virtual bool in_hitbox(sf::FloatRect &rect);
private:

};
