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
#include "graphics.h"
#include <iostream>
#include <vector>
#include <map>
#include <memory>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>  

int main() {

    Board board;
    std::vector<std::vector<std::unique_ptr<Piece>>>& currBoard = board.getCurrBoard();
    char turn = 'w';

    // Create a window with a size of 640x640 pixels (8x8 board of 80x80)
    sf::RenderWindow window(sf::VideoMode({640, 640}), "Chessboard");

    for (int i = 0; i<8; i++) {
        for (int j = 0; j<8; j++) {
            auto& tempPiece = currBoard[i][j];
        }
    }

    bool piecesDrawn = false;
    Graphics::draw_window(window, board);
    piecesDrawn = true;

    // Loop until the window is closed
    while (window.isOpen()) {
        // Provide handlers for concrete types and fall back to generic handler
        window.handleEvents(
            [&](const sf::Event::Closed&) { window.close(); },
            [&](const sf::Event::MouseButtonPressed& button) { 
                if (button.button == sf::Mouse::Button::Left){
                    auto [x, y] = Helpers::get_coords(button.position.x, button.position.y);
                    auto& sourcePiece = currBoard.at(x).at(y);
                    std::cout << sourcePiece->getColour() << sourcePiece->getName();
                    std::cout << "Vector: (" << button.position.x << ", " << button.position.y << ")\n";

                }
            }
        );
    }
}



    //board.printBoard(currBoard);
    /*
    while (true) {
        std::vector<std::vector<int>> positions = Helpers::takeInput(turn);
        std::vector<int> startPos = positions.at(0);
        std::vector<int> endPos = positions.at(1);
        //clear square for bishop valid move test
        currBoard.at(1).at(1) = std::make_unique<Empty>(startPos);
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