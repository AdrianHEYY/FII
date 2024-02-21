#include "keyboard.h"

#include <set>

namespace util
{
	namespace keyboard 
	{
		std::set<sf::Keyboard::Key> _just_pressed;
		std::set<sf::Keyboard::Key> _just_released;
		std::set<sf::Keyboard::Key> _pressed;
		bool just_pressed(sf::Keyboard::Key key) {
			auto fi = _just_pressed.find(key);
			if (fi == _just_pressed.end()) return 0;
			return 1;
		}
		bool just_released(sf::Keyboard::Key key) {
			auto fi = _just_released.find(key);
			if (fi == _just_released.end()) return 0;
			return 1;
		}
		bool is_pressed(sf::Keyboard::Key key) {
			auto fi = _pressed.find(key);
			if (fi == _pressed.end()) return 0;
			return 1;
		}
		void update_key(sf::Keyboard::Key key, bool just_pressed_key) {
			if (just_pressed_key == 1 && !is_pressed(key)) {
				_just_pressed.insert(key);
				_pressed.insert(key);
			}
			else if (just_pressed_key == 0) {
				_just_released.insert(key);
				_pressed.erase(key);
			}
		}
		void update_frame() {
			_just_pressed.clear();
			_just_released.clear();
		}
	}
}