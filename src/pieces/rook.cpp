#include "rook.h"
#include <vector>
#include <memory>
#include "../helpers.h"

bool Rook::validMove(std::vector<int> v, const std::vector<std::vector<std::unique_ptr<Piece>>>& board) {

    Helpers::MoveContext m = getMoveContext(v);

    // Out of bounds
    if (m.destRow < 0 || m.destRow > 7 || m.destCol < 0 || m.destCol > 7) return false;

    // Not a rook move
    if (m.destRow != m.currRow && m.destCol != m.currCol) return false;

    // Moving horizontally
    if (m.destRow == m.currRow) {
        int step = (m.destCol > m.currCol) ? 1 : -1;
        for (int c = m.currCol + step; c != m.destCol; c += step) {
            if (board.at(m.currRow).at(c)->getName() != "None") return false;
        }
    }
    // Moving vertically
    else {
        int step = (m.destRow > m.currRow) ? 1 : -1;
        for (int r = m.currRow + step; r != m.destRow; r += step) {
            if (board.at(r).at(m.currCol)->getName() != "None") return false;
        }
    }

    // Final square: must be empty or enemy piece
    auto& destPiece = board.at(m.destRow).at(m.destCol);
    return destPiece->getName() == "None" || destPiece->getColour() == m.oppColour;
}