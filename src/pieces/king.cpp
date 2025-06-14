#include "king.h"
#include <memory>
#include <vector>
#include <cmath>
#include "../helpers.h"

bool King::validMove(std::vector<int> v, const std::vector<std::vector<std::unique_ptr<Piece>>>& board) {
    
    Helpers::MoveContext m = getMoveContext(v);

    //check if out of bounds
    if ((m.destRow < 0 || m.destRow > 7) || (m.destCol < 0 || m.destCol > 7)) {
        return false;
    }

    auto &destPiece = board.at(m.destRow).at(m.destCol);
    if (destPiece->getColour() == m.currColour) {
        return false;
    }

    int rowDiff = std::abs(m.destRow - m.currRow);
    int colDiff = std::abs(m.destCol - m.currCol);

    // King can move one square in any direction
    if (rowDiff <= 1 && colDiff <= 1 && (rowDiff != 0 || colDiff != 0)) {
        return true;
    }

    return false;

}