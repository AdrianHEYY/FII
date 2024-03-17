#include "keyboard.h"

#include <set>

namespace util
{
	namespace keyboard 
	{
		bool just_pressed_a_key = 0;
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
			if (just_pressed_key == 1 && !is_pressed(key)) { // ty windows api for being a bitch (semnalu de la released e tot 1, ca si cum ai apasa din nou tasta)
				_just_pressed.insert(key);
				just_pressed_a_key = 1;
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
			just_pressed_a_key = 0;
		}
	}
}