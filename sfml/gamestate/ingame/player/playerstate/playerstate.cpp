#include "playerstate.h"

#include "../../../../util/util.h"

Player_State::Player_State() {

}

void Player_State::draw() {
	util::window.draw(sprite);
}

void Player_State::update() {

}