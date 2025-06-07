#include "knight.h"
#include <vector>
#include <memory>
#include <cmath>
#include "../helpers.h"

bool Knight::validMove(std::vector<int> v, const std::vector<std::vector<std::unique_ptr<Piece>>>& board) {

    Helpers::MoveContext m = getMoveContext(v);

    //check if out of bounds
    if ((m.destRow < 0 || m.destRow > 7) || (m.destCol < 0 || m.destCol > 7)) {
        return false;
    }

    //check if valid knight move
    if (std::abs(m.destRow - m.currRow) == 2) {
        if (std::abs(m.destCol - m.currCol) != 1) {
            return false;
        }
    }
    else if (std::abs(m.destRow - m.currRow) == 1) {
        if (std::abs(m.destCol - m.currCol) != 2) {
            return false;
        }
    }
    else {return false;}

    //check destination tile
    auto& tempPiece = board.at(m.destRow).at(m.destCol);
    return (tempPiece->getName() == "None" || tempPiece->getColour() == m.oppColour) ?  true : false;

}