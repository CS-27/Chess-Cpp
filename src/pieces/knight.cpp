#include "knight.h"
#include <vector>
#include <memory>
#include <cmath>

bool Knight::validMove(std::vector<int> v, const std::vector<std::vector<std::unique_ptr<Piece>>>& board) {

    //get new and curr col/row and currcColour
    int newRow, newCol;
    newRow = v.at(0);
    newCol = v.at(1);
    std::vector<int> coords  = getCoords();
    char currColour = getColour();
    int currRow = coords.at(0);
    int currCol = coords.at(1);
    char oppColour = (currColour == 'b') ? 'w' : 'b';

    //check if out of bounds
    if ((newRow < 0 || newRow > 7) || (newCol < 0 || newCol > 7)) {
        return false;
    }

    //check if valid knight move
    if (std::abs(newRow - currRow) == 2) {
        if (std::abs(newCol - currCol) != 1) {
            return false;
        }
    }
    else if (std::abs(newRow - currRow) == 1) {
        if (std::abs(newCol - currCol) != 2) {
            return false;
        }
    }
    else {return false;}

    //check destination tile
    auto& tempPiece = board.at(newRow).at(newCol);
    return (tempPiece->getName() == "None" || tempPiece->getColour() == oppColour) ?  true : false;

}