#ifndef BOARD_H
#define BOARD_H

#include "piece.h"
#include "pieces/rook.h"
#include "pieces/knight.h"
#include "pieces/bishop.h"
#include "pieces/king.h"
#include "pieces/queen.h"
#include "pieces/pawn.h"
#include <vector>
#include <memory>


class Board {
    private:
        std::vector<std::vector<std::shared_ptr<Piece>>> currBoard;
    public:
        Board();
        std::vector<std::vector<std::shared_ptr<Piece>>>& getCurrBoard() {
            return currBoard;
        }

        void printBoard(std::vector<std::vector<std::shared_ptr<Piece>>>&) const;
        
};

#endif