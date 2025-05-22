#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <SFML/Graphics.hpp>
#include "board.h"

namespace Graphics {
    void draw_window(sf::RenderWindow &window, Board &board);
};

#endif