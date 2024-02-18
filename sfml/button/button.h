#pragma once

#include <SFML/Graphics.hpp>

class button {
public:
	button(std::string filepath_normal, std::string filepath_hover, std::string filepath_pressed);
	button();
	void update();
	void draw();
	inline void setSize(sf::Vector2f size) { sprite.setSize(size); };
	inline sf::Vector2f getSize() { return sprite.getSize(); };
	inline void setPosition(sf::Vector2f position) { sprite.setPosition(position); };
	inline sf::Vector2f getPosition() { return sprite.getPosition(); };
private:
	sf::RectangleShape sprite;
	sf::Texture normal, hover, pressed;
	sf::Texture* current_texture = nullptr;
};