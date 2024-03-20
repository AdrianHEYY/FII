#include "void.h"

#include "../../../../util/util.h"
#include "../../ingame.h"

Void::Void(in_game *ingame, sf::Vector2f position, sf::Vector2f size) {
	ingame = ingame;

	position += sf::Vector2f(2, 1);
	size += sf::Vector2f(1, 0);

	int cate = 20;
	im.create(1, cate);
	float step = 255 / cate;
	for (int i = 0; i < cate; i++) {
		int val = (i + 1) * step;
		im.setPixel(0, i, sf::Color(val, val, val, 255));
	}
	//im.setPixel(0, 0, sf::Color(85, 85, 85, 255));
	//im.setPixel(0, 1, sf::Color(170, 170, 170));
	//im.setPixel(0, 2, sf::Color::White);
	tex.loadFromImage(im);
	sprite.setTexture(&tex);
	sprite.setPosition(position);
	sprite.setSize(size);

	hitbox_off = sf::Vector2f(0, size.y / 2.0f);
	hitbox_size = sf::Vector2f(size.x, size.y / 2.0f);
}

void Void::draw() {
	util::window.draw(sprite);
}

bool Void::in_hitbox(sf::FloatRect& rect) {
	sf::FloatRect a(sprite.getPosition() + hitbox_off, hitbox_size);
	if (a.intersects(rect) == 1) {
		return 1;
	}
	return 0;
}