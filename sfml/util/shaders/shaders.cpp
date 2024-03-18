#include "shaders.h"

#include "../util.h"

namespace util {
	namespace shaders {
		sf::Shader vignette;
		void init() {
			vignette.loadFromFile("shaders/vignette.vert", "shaders/vignette.frag");
			vignette.setUniform("iResolution", sf::Vector2f(util::window.getSize()));
		}
	}
}