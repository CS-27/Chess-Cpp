#include "graphics.h"
#include <SFML/Graphics.hpp>
#include "board.h"
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include "piece.h"

void Graphics::draw_window(sf::RenderWindow &window, Board &board) {

    auto& currBoard = board.getCurrBoard();
    window.clear(sf::Color::White);
    // Create a rectangle shape for the squares
    sf::RectangleShape square(sf::Vector2f({80.f, 80.f}));
    // Loop to create an 8x8 grid (64 squares in total)
    for (int row = 0; row < 8; ++row) {
        for (int col = 0; col < 8; ++col) {
            // Calculate position of each square
            square.setPosition({col * 80.f, row * 80.f});

            // Alternate colors based on row and column (like a chessboard)
            if ((row + col) % 2 == 0) {
                sf::Color color(245, 245, 220);
                square.setFillColor(color);  // White square
            } else {
                square.setFillColor(sf::Color::Blue);  // Black square
            }

            // Draw the square onto the window
            window.draw(square);
        }
    }

    float desiredWidth = 80.f;
    float desiredHeight = 80.f;
    
    for (int row = 0; row < 8; ++row) {
        for (int col = 0; col < 8; ++col) {

            auto& piece = currBoard.at(row).at(col);

            sf::Vector2u textureSize = piece->getTexture().getSize();
            float scaleX = desiredWidth / textureSize.x;
            float scaleY = desiredHeight / textureSize.y;

            auto& img = piece->getSprite();
            img.setScale(sf::Vector2f(scaleX, scaleY));

            float x = col * 80; //flipped due to board drawing logic
            float y = row * 80; //same
            img.setPosition(sf::Vector2f(x, y));

            window.draw(img);
        }
    }

    window.display();
};
