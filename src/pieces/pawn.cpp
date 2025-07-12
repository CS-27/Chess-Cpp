#include "pawn.h"
#include <memory>
#include <vector>
#include "../helpers.h"
#include "../board.h"

bool Pawn::validMove(std::vector<int> v, const Board& b) {

    std::vector<int> EPtarget = b.EnPassantTargetCoords;

    auto& board = b.getCurrBoard();

    Helpers::MoveContext m = getMoveContext(v);

    //check if out of bounds
    if ((m.destRow < 0 || m.destRow > 7) || (m.destCol < 0 || m.destCol > 7)) {
        return false;
    }

    //if pawn is in row 1 or row 6 then it can move 2 forward
        //presuming that the whole path is clear
    int twoMoveRow = (m.currColour == 'b') ? 1 : 6;

    if (m.currRow == twoMoveRow) {
        if (m.currColour == 'b') {
            if ((m.destRow - m.currRow == 2) && (m.currCol == m.destCol)) {
                if ((board.at(m.destRow-1).at(m.destCol)->getName() == "None") && (board.at(m.destRow).at(m.destCol)->getName() == "None")) {
                    return true;
                }
            }
        }
        else {
            if ((m.currRow - m.destRow == 2) && (m.currCol == m.destCol)) {
                if ((board.at(m.destRow+1).at(m.destCol)->getName() == "None") && (board.at(m.destRow).at(m.destCol)->getName() == "None")) {
                    return true;
                }
            }
        }
    }
    
    //else pawn can move 1 forward if clear
    if ((m.destRow - m.currRow == 1) && (m.currCol == m.destCol) && (m.currColour == 'b') && (board.at(m.destRow).at(m.destCol)->getName() == "None")) {
        return true;
    }
    else if ((m.currRow - m.destRow == 1) && (m.currCol == m.destCol) && (m.currColour == 'w') && (board.at(m.destRow).at(m.destCol)->getName() == "None")) {
        return true;
    }

    std::vector<int> destCoords = {m.destRow, m.destCol};
    //white: if row + 1, (col - 1 || col + 1) is opp colour piece
        //valid move
    if ((m.destRow - m.currRow == 1) && 
        (std::abs(m.destCol - m.currCol) == 1) && 
        ((board.at(m.destRow).at(m.destCol)->getColour() == 'w') || (destCoords == EPtarget)) && 
        (getColour() == 'b')) {
        return true;
    }
    
    //black: if row - 1, (col - 1 || col + 1) is opp colour piece
        //valid move
    if ((m.currRow - m.destRow == 1) && 
        (std::abs(m.destCol - m.currCol) == 1) && 
        ((board.at(m.destRow).at(m.destCol)->getColour() == 'b') || (destCoords == EPtarget)) && 
        (getColour() == 'w')) {
        return true;
    }

    return false;
}

