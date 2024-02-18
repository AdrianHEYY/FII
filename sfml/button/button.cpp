#include "button.h"

#include "../util/util.h"
#include "../util/mouse/mouse.h"

button::button(std::string filepath_normal, std::string filepath_hover, std::string filepath_pressed) {
	normal.loadFromFile(filepath_normal);
	hover.loadFromFile(filepath_hover);
	pressed.loadFromFile(filepath_pressed);

	current_texture = &normal;
	sprite.setTexture(current_texture);
}

button::button() {
	throw std::runtime_error("We muie esti prost, nu ai pus filepathuri calumea!");
}

void button::update() {
	if (util::mouse::is_pressed() == 1) {
		if (util::mouse::is_hovering(sprite) == 1) { // pressed
			if (current_texture != &pressed) {
				current_texture = &pressed;
				sprite.setTexture(current_texture);
			}
		}
	}
	else {
		if (util::mouse::is_hovering(sprite) == 1) { // hovering
			if (current_texture != &hover) {
				current_texture = &hover;
				sprite.setTexture(current_texture);
			}
		}
		else { // normal
			if (current_texture != &normal) {
				current_texture = &normal;
				sprite.setTexture(current_texture);
			}
		}
	}
}
void button::draw() {
	util::window.draw(sprite);
}