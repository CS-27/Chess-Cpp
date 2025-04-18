#include "piece.h"
#include "helpers.h"
#include "pieces/rook.h"
#include "pieces/knight.h"
#include "pieces/bishop.h"
#include "pieces/king.h"
#include "pieces/queen.h"
#include "pieces/pawn.h"
#include "pieces/empty.h"
#include "board.h"
#include <iostream>
#include <vector>
#include <map>
#include <memory>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>  

int main() {

    Board board;
    std::vector<std::vector<std::shared_ptr<Piece>>> currBoard = board.getCurrBoard();
    char turn = 'w';

    // Create a window with a size of 640x640 pixels (8x8 board of 80x80)
    sf::RenderWindow window(sf::VideoMode({640, 640}), "Chessboard");

    // Create a rectangle shape for the squares
    sf::RectangleShape square(sf::Vector2f({80.f, 80.f}));

    // Loop until the window is closed
    while (window.isOpen()) {
        while (const std::optional event = window.pollEvent()) {
            //if (event->is<sf::Event::Closed>() ||
            //(event->is<sf::Event::KeyPressed>() &&
            // event->getIf<sf::Event::KeyPressed>()->code == sf::Keyboard::Key::Escape)) {
            //    window.close();
            // }
            

            // Clear the window with a white background
            window.clear(sf::Color::White);

            // Loop to create an 8x8 grid (64 squares in total)
            for (int row = 0; row < 8; ++row) {
                for (int col = 0; col < 8; ++col) {
                    // Calculate position of each square
                    square.setPosition({col * 80.f, row * 80.f});

                    // Alternate colors based on row and column (like a chessboard)
                    if ((row + col) % 2 == 0) {
                        square.setFillColor(sf::Color::White);  // White square
                    } else {
                        square.setFillColor(sf::Color::Black);  // Black square
                    }

                    // Draw the square onto the window
                    window.draw(square);
                }
            }

            // Display everything we've drawn
            window.display();
        

            // Provide handlers for concrete types and fall back to generic handler
            window.handleEvents(
                [&](const sf::Event::Closed&) { window.close(); },
                [&](const sf::Event::MouseButtonPressed& button) { 
                    if (button.button == sf::Mouse::Button::Left){
                        int x = button.position.y / 80;
                        int y = button.position.x / 80;
                        std::shared_ptr<Piece> piece = currBoard.at(x).at(y);
                        std::cout << piece->getName();
                        std::cout << "Vector: (" << button.position.x << ", " << button.position.y << ")\n";
                    }
                }
            );
        }
    }
}


    //board.printBoard(currBoard);
    /*
    while (true) {
        std::vector<std::vector<int>> positions = Helpers::takeInput(turn);
        std::vector<int> startPos = positions.at(0);
        std::vector<int> endPos = positions.at(1);
        //clear square for bishop valid move test
        currBoard.at(1).at(1) = std::make_shared<Empty>(startPos);
        board.printBoard(currBoard);
        auto piece = currBoard.at(startPos.at(0)).at(startPos.at(1));
        if (piece->validMove(endPos, currBoard)) {
            std::cout << "true" << std::endl;
            Helpers::movePiece(startPos, endPos, piece);
        }
        else {
        }
        //piece->setCoords(newCoords, currBoard);
        board.printBoard(currBoard);
        Helpers::toggleTurn(turn);
    }
    */