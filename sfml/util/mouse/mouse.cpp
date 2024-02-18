#include "mouse.h"

namespace util {
	namespace mouse {
		bool _just_pressed = 0;
		bool _just_released = 0;
		bool _is_pressed = 0;
		bool just_pressed() {
			return _just_pressed;
		}
		bool just_released() {
			return _just_released;
		}
		bool is_pressed() {
			return _is_pressed;
		}
		void update_frame() {
			_just_pressed = 0;
			_just_released = 0;
		}
		void update_state(sf::Mouse::Button button, bool just_pressed) {
			if (button == sf::Mouse::Left) {
				if (just_pressed == 1) {
					_just_pressed = 1;
					_is_pressed = 1;
				}
				else {
					_just_released = 1;
					_is_pressed = 0;
				}
			}
		}
		bool is_hovering(sf::RectangleShape& rect) {
			sf::Vector2i mousePosition = sf::Mouse::getPosition();
			sf::Vector2f rectPosition = rect.getPosition();
			sf::Vector2f rectSize = rect.getSize();

			if (mousePosition.x >= rectPosition.x &&
				mousePosition.x <= rectPosition.x + rectSize.x &&
				mousePosition.y >= rectPosition.y &&
				mousePosition.y <= rectPosition.y + rectSize.y) {
				return true;
			}
			return false;
		}
	}
}