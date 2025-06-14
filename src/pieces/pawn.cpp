#include "pawn.h"
#include <memory>
#include <vector>
#include "../helpers.h"

bool Pawn::validMove(std::vector<int> v, const std::vector<std::vector<std::unique_ptr<Piece>>>& board) {

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
                if (m.destRow - m.currRow == 2) {
                    if ((board.at(m.destRow-1).at(m.destCol)->getName() == "None") && (board.at(m.destRow).at(m.destCol)->getName() == "None")) {
                        return true;
                    }
                }
            }
            else {
                if (m.currRow - m.destRow == 2) {
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

        //white: if row + 1, (col - 1 || col + 1) is opp colour piece
            //valid move
        if ((m.destRow - m.currRow == 1) && (std::abs(m.destCol - m.currCol) == 1) && (board.at(m.destRow).at(m.destCol)->getColour() == 'w') && (getColour() == 'b')) {
            return true;
        }
        
        //black: if row - 1, (col - 1 || col + 1) is opp colour piece
            //valid move
        if ((m.currRow - m.destRow == 1) && (std::abs(m.destCol - m.currCol) == 1) && (board.at(m.destRow).at(m.destCol)->getColour() == 'b') && (getColour() == 'w')) {
            return true;
        }

        return false;
}

