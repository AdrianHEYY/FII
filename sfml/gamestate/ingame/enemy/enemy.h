#pragma once

#include <SFML/Graphics.hpp>
#include <fstream>
#include "../../../util/util.h"

class Enemy {
public:
	Enemy();
	virtual void update(float delta_time);
	virtual void draw(sf::RenderWindow& win);
	virtual void save_file(std::ofstream& stream);
private:

};
