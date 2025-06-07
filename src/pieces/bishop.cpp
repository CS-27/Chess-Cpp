#include "bishop.h"
#include <vector>
#include <memory>
#include "../helpers.h"

bool Bishop::validMove(std::vector<int> v, const std::vector<std::vector<std::unique_ptr<Piece>>>& board) {

    Helpers::MoveContext m = getMoveContext(v);

    // out of bounds
    if (m.destRow < 0 || m.destRow > 7 || m.destCol < 0 || m.destCol > 7) return false;

    // must move diagonally
    if (std::abs(m.destRow - m.currRow) != std::abs(m.destCol - m.currCol)) return false;

    // walk diagonally
    int rowStep = (m.destRow > m.currRow) ? 1 : -1;
    int colStep = (m.destCol > m.currCol) ? 1 : -1;

    int r = m.currRow + rowStep;
    int c = m.currCol + colStep;
    while (r != m.destRow && c != m.destCol) {
        if (board.at(r).at(c)->getName() != "None") {
            return false;
        }
        r += rowStep;
        c += colStep;
    }

    auto& dest = board.at(m.destRow).at(m.destCol);
    return (dest->getName() == "None" || dest->getColour() == m.oppColour);
}