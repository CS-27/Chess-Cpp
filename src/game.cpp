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

    // Create a window with a size of 640x640 pixels (8x8 board of 80x80)
    sf::RenderWindow window(sf::VideoMode({640, 640}), "Chessboard");

    bool piecesDrawn = false;
    bool pieceMoved = false;
    std::vector<int> sourceCoords;
    std::vector<int> destCoords;
    char turn = 'w';
    bool selected = false;

    // Loop until the window is closed
    while (window.isOpen()) {
        while (!piecesDrawn) {
            Graphics::draw_window(window, board);
            std::cout << "drawing board";
            piecesDrawn = true;
        }
        // Provide handlers for concrete types and fall back to generic handler
        window.handleEvents(
            [&](const sf::Event::Closed&) { window.close(); },
            [&](const sf::Event::MouseButtonPressed& button) { 
            
                if (button.button == sf::Mouse::Button::Left){
                    auto [x, y] = Helpers::get_coords(button.position.x, button.position.y);
                    auto& tempPiece = board.getPiece(std::vector<int>{x,y});
                    tempPiece->printPiece();

                    //  Piece has been selected, now choosing destination square/Piece
                    if (!sourceCoords.empty() && destCoords.empty() && selected == true && tempPiece->getColour() != turn) {
                        destCoords = tempPiece->getCoords();
                        std::cout << "destination selected ";
                        tempPiece->printPiece();
                    }

                    //  Selecting Piece
                    else if (tempPiece->getColour() == turn) {
                        sourceCoords = tempPiece->getCoords();
                        selected = true;
                        std::cout << "selected Piece ";
                        tempPiece->printPiece();
                    }

                    // Source and Dest squares have been selected
                    if (!sourceCoords.empty() && !destCoords.empty()) {
                        board.movePiece(sourceCoords, destCoords);
                        Helpers::toggleTurn(turn);
                        sourceCoords.clear();
                        destCoords.clear();
                        selected = false;
                        std::cout << "swapped Piece, original square should be empty";
                        piecesDrawn = false;
                    }

                    
                }
            }
        );
    }
}