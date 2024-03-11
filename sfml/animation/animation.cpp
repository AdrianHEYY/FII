#include "animation.h"

#include <fstream>
#include <iostream>

Animation::Animation(std::string filepath, sf::RectangleShape *sprite) {
	tex.loadFromFile(filepath + ".png");
	sprite->setTexture(&tex);
	this->sprite = sprite;
	
	std::ifstream in;
	in.open(filepath + ".txt");
	if (!in.is_open()) {
		throw std::runtime_error("nu s-a deschis text-file-ul cu informatiile despre aniatie");
	}
	int x;
	while (in >> x) {
		frame_times.push_back(x);
	}
	frame_height = tex.getSize().y;
	frame_width = tex.getSize().x / frame_times.size();
	
	reset();
}
void Animation::reset() {
	current_frame = 0;
	sprite->setTextureRect(sf::IntRect(0, 0, frame_width, frame_height));
	last_time = std::chrono::high_resolution_clock::now();
}
void Animation::update() {
	int old_frame = current_frame;
	
	std::chrono::high_resolution_clock::time_point now = std::chrono::high_resolution_clock::now();
	long long duration = std::chrono::duration_cast<std::chrono::milliseconds>(now - last_time).count();
	while (frame_times[current_frame] <= duration) {
		duration -= frame_times[current_frame];
		current_frame++;
		current_frame %= frame_times.size();
		last_time = now;
	}

	if (old_frame != current_frame) {
		if (sprite->getTexture() != &tex) sprite->setTexture(&tex);

		if (is_mirrored == 0) {
			sprite->setTextureRect(sf::IntRect(current_frame * frame_width, 0, frame_width, frame_height));
		}
		else {
			sprite->setTextureRect(sf::IntRect(current_frame * frame_width + frame_width, 0, -frame_width, frame_height));
		}

	}
}

void Animation::mirror(bool is_mirrored) {
	this->is_mirrored = is_mirrored;
}