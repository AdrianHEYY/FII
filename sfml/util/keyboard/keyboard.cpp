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
		
        std::string fromKtoS(const sf::Keyboard::Key& k) {
            std::string ret;
            switch (k) {
            case sf::Keyboard::A:
                ret = "A";
                break;
            case sf::Keyboard::B:
                ret = "B";
                break;
            case sf::Keyboard::C:
                ret = "C";
                break;
            case sf::Keyboard::D:
                ret = "D";
                break;
            case sf::Keyboard::E:
                ret = "E";
                break;
            case sf::Keyboard::F:
                ret = "F";
                break;
            case sf::Keyboard::G:
                ret = "G";
                break;
            case sf::Keyboard::H:
                ret = "H";
                break;
            case sf::Keyboard::I:
                ret = "I";
                break;
            case sf::Keyboard::J:
                ret = "J";
                break;
            case sf::Keyboard::K:
                ret = "K";
                break;
            case sf::Keyboard::L:
                ret = "L";
                break;
            case sf::Keyboard::M:
                ret = "M";
                break;
            case sf::Keyboard::N:
                ret = "N";
                break;
            case sf::Keyboard::O:
                ret = "O";
                break;
            case sf::Keyboard::P:
                ret = "P";
                break;
            case sf::Keyboard::Q:
                ret = "Q";
                break;
            case sf::Keyboard::R:
                ret = "R";
                break;
            case sf::Keyboard::S:
                ret = "S";
                break;
            case sf::Keyboard::T:
                ret = "T";
                break;
            case sf::Keyboard::U:
                ret = "U";
                break;
            case sf::Keyboard::V:
                ret = "V";
                break;
            case sf::Keyboard::W:
                ret = "W";
                break;
            case sf::Keyboard::X:
                ret = "X";
                break;
            case sf::Keyboard::Y:
                ret = "Y";
                break;
            case sf::Keyboard::Z:
                ret = "Z";
                break;
            case sf::Keyboard::Num0:
                ret = "0";
                break;
            case sf::Keyboard::Num1:
                ret = "1";
                break;
            case sf::Keyboard::Num2:
                ret = "2";
                break;
            case sf::Keyboard::Num3:
                ret = "3";
                break;
            case sf::Keyboard::Num4:
                ret = "4";
                break;
            case sf::Keyboard::Num5:
                ret = "5";
                break;
            case sf::Keyboard::Num6:
                ret = "6";
                break;
            case sf::Keyboard::Num7:
                ret = "7";
                break;
            case sf::Keyboard::Num8:
                ret = "8";
                break;
            case sf::Keyboard::Num9:
                ret = "9";
                break;
            case sf::Keyboard::LBracket:
                ret = "[";
                break;
            case sf::Keyboard::RBracket:
                ret = "]";
                break;
            case sf::Keyboard::SemiColon:
                ret = ";";
                break;
            case sf::Keyboard::Comma:
                ret = ",";
                break;
            case sf::Keyboard::Period:
                ret = ".";
                break;
            case sf::Keyboard::Quote:
                ret = "\"";
                break;
            case sf::Keyboard::Slash:
                ret = "/";
                break;
            case sf::Keyboard::BackSlash:
                ret = "\\";
                break;
            case sf::Keyboard::Tilde:
                ret = "`";
                break;
            case sf::Keyboard::Equal:
                ret = "=";
                break;
            case sf::Keyboard::Space:
                ret = "_";
                break;
            case sf::Keyboard::Left:

                ret = "<";
                break;
            case sf::Keyboard::Right:

                ret = ">";
                break;
            case sf::Keyboard::Up:
                ret = "^";
                break;
            case sf::Keyboard::Down:
                ret = "v";
                break;
            default:
                ret = "Unknown";
                break;
            }
            return ret;
        }

		extern sf::Keyboard::Key 
			move_left_key = sf::Keyboard::A, move_right_key, jump_key,
			crouch_key, wall_grab_key, big_jump_key, dash_key;
	}
}