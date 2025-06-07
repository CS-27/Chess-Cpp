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
        std::vector<std::vector<std::unique_ptr<Piece>>> currBoard;
    public:
        Board();
        std::vector<std::vector<std::unique_ptr<Piece>>>& getCurrBoard() {
            return currBoard;
        }

        void printBoard(std::vector<std::vector<std::unique_ptr<Piece>>>&) const;

        bool movePiece(std::vector<int>& sourceCoords, std::vector<int>& destCoords);

        std::unique_ptr<Piece>& getPiece(std::vector<int> sourceCoords) {
            return currBoard.at(sourceCoords.at(0)).at(sourceCoords.at(1));
        }

        bool isEmpty(int row, int col) {
            return (currBoard.at(row).at(col)->getName() == "None") ? true : false;
        }
        
};

#endif