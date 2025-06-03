#include "rook.h"
#include <vector>
#include <memory>

bool Rook::validMove(std::vector<int> v, const std::vector<std::vector<std::unique_ptr<Piece>>>& board) {
    int newRow, newCol;
    newRow = v.at(0);
    newCol = v.at(1);
    std::vector<int> coords  = getCoords();
    char currColour = getColour();
    int currRow = coords.at(0);
    int currCol = coords.at(1);
    char oppColour = (currColour == 'b') ? 'w' : 'b';
    

    if ((newRow < 0 || newRow > 7) || (newCol < 0 || newCol > 7)) {
        return false;
    }

    if (newRow == currRow) {
        if (newCol == currCol) {
            return false;
        }
        else if (newCol < currCol) {
            for (int i = currCol-1; i >= newCol; i--) {
                if (i == newCol) {
                    auto& tempPiece = board.at(currRow).at(i);
                    return (tempPiece->getName() == "None" || tempPiece->getColour() == oppColour) ? true : false;
                }
                else if (board.at(currRow).at(i)->getName() != "None") {
                    return false;
                }
            }
        }
        else if (newCol > currCol) {
            for (int i = currCol+1; i <= newCol; i++) {
                if (i == newCol) {
                    auto& tempPiece = board.at(currRow).at(i);
                    return (tempPiece->getName() == "None" || tempPiece->getColour() == oppColour) ? true : false;
                }
                else if (board.at(currRow).at(i)->getName() != "None") {
                    return false;
                }
            }
        }
    }

    if (newCol == currCol) {
        if (newRow == currRow) {
            return false;
        }
        else if (newRow < currRow) {
            for (int i = currRow-1; i >= newRow; i--) {
                if (i == newRow) {
                    auto& tempPiece = board.at(i).at(currCol);
                    return (tempPiece->getName() == "None" || tempPiece->getColour() == oppColour) ? true : false;
                }
                else if (board.at(i).at(currCol)->getName() != "None") {
                    return false;
                }
            }
        }
        else if (newRow > currRow) {
            for (int i = currRow+1; i <= newRow; i++) {
                if (i == newRow) {
                    auto& tempPiece = board.at(i).at(currCol);
                    return (tempPiece->getName() == "None" || tempPiece->getColour() == oppColour) ? true : false;
                }
                else if (board.at(i).at(currCol)->getName() != "None") {
                    return false;
                }
            }
        }
    }
    return false;
}