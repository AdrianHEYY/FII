#include "util.h"

namespace util {
    const int window_size_x = sf::VideoMode::getDesktopMode().width;
    const int window_size_y = sf::VideoMode::getDesktopMode().height;
    sf::RenderWindow renderwindow(sf::VideoMode(window_size_x, window_size_y), "Title", sf::Style::Fullscreen);
    sf::RenderTexture window;
    bool big_done = 0;
    
    float delta_time;

    float convert_ms_to_frames(int ms) {
        return float(ms) * 144.0 / 1000.0;
    }

    sf::Font font;

    bool rect_collision(sf::RectangleShape& a, sf::RectangleShape& b) {
        sf::Vector2f posA = a.getPosition();
        sf::Vector2f sizeA = a.getSize();
        sf::Vector2f posB = b.getPosition();
        sf::Vector2f sizeB = b.getSize();

        bool xCollision = posA.x < posB.x + sizeB.x &&
            posA.x + sizeA.x > posB.x;

        bool yCollision = posA.y < posB.y + sizeB.y &&
            posA.y + sizeA.y > posB.y;

        return xCollision && yCollision;
    }
}