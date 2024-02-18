#pragma once

#include <SFML/Graphics.hpp>

enum player_states {
	SIMPLU, 
	GRAS,
	FURIOS
};

class Player_State {
public:
	Player_State();

	inline sf::RectangleShape& get_sprite() {return sprite;};

	void draw();
	virtual void update();
private:
	
protected:
	sf::RectangleShape sprite;
	sf::Texture texture;
};