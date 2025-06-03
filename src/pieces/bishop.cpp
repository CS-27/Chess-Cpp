#include "bishop.h"
#include <vector>
#include <memory>

bool Bishop::validMove(std::vector<int> v, const std::vector<std::vector<std::unique_ptr<Piece>>>& board) {

    //get new and curr col/row and currcColour
    int newRow, newCol;
    newRow = v.at(0);
    newCol = v.at(1);
    std::vector<int> coords  = getCoords();
    char currColour = getColour();
    int currRow = coords.at(0);
    int currCol = coords.at(1);
    char oppColour = (currColour == 'b') ? 'w' : 'b';

    //check if slope is 1
    if (std::abs(newCol - currCol) != std::abs(newRow - currRow)) {
        return false;
    }

    //check if out of bounds
    if ((newRow < 0 || newRow > 7) || (newCol < 0 || newCol > 7)) {
        return false;
    }

    //check if not a valid bishop move
    if (newRow == currRow || newCol == currCol) {
            return false;
    }

    //check if diagonal path is clear
    if (newRow < currRow) {
        if (newCol < currCol) {
            for (int i = currRow-1; i > newRow; i--) {
                for (int j = currCol-1; j > newCol; j--) {
                    auto& tempPiece = board.at(i).at(j);
                    if (tempPiece->getName() != "None") {
                        return false;
                    }
                }
            }
        }
        else if (newCol > currCol) {
            for (int i = currRow-1; i > newRow; i--) {
                for (int j = currCol+1; j < newCol; j++) {
                    auto& tempPiece = board.at(i).at(j);
                    if (tempPiece->getName() != "None") {
                        return false;
                    }
                }
            }
        }
    }

    else if (newRow > currRow) {
        if (newCol < currCol) {
            for (int i = currRow+1; i < newRow; i++) {
                for (int j = currCol-1; j > newCol; j--) {
                    auto& tempPiece = board.at(i).at(j);
                    if (tempPiece->getName() != "None") {
                        return false;
                    }
                }
            }
        }
        else if (newCol > currCol) {
            for (int i = currRow+1; i < newRow; i++) {
                for (int j = currCol+1; j < newCol; j++) {
                    auto& tempPiece = board.at(i).at(j);
                    if (tempPiece->getName() != "None") {
                        return false;
                    }
                }
            }
        }
    }

    //check destination tile
    auto& tempPiece = board.at(newRow).at(newCol);
    return (tempPiece->getName() == "None" || tempPiece->getColour() == oppColour) ?  true : false;
    
};