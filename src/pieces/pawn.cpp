#include "pawn.h"
#include <memory>
#include <vector>

bool Pawn::validMove(std::vector<int> v, const std::vector<std::vector<std::unique_ptr<Piece>>>& board) {

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

        //if pawn is in row 1 or row 6 then it can move 2 forward
            //presuming that the whole path is clear
        
        //else pawn can move 1 forward if clear

        //white: if row + 1, (col - 1 || col + 1) is opp colour piece
            //valid move
        
        //black: if row - 1, (col - 1 || col + 1) is opp colour piece
            //valid move
        
        return true;
}