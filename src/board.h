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
#include <string>



class Board {
    private:
        std::vector<std::vector<std::unique_ptr<Piece>>> currBoard;

    public:
        Board();

        const std::vector<std::vector<std::unique_ptr<Piece>>>& getCurrBoard() const {
            return currBoard;
        }

        mutable bool enPassantAccepted = false;
        mutable bool enPassantOppLast = false;
        mutable bool enPassantOpp = false;
        mutable std::vector<int> EnPassantTargetCoords;
        mutable std::vector<int> EnPassantPieceToReplace;

        void printBoard(std::vector<std::vector<std::unique_ptr<Piece>>>&) const;

        bool movePiece(const std::vector<int>& sourceCoords, const std::vector<int>& destCoords);

        std::unique_ptr<Piece>& getPiece(std::vector<int> sourceCoords) {
            return currBoard.at(sourceCoords.at(0)).at(sourceCoords.at(1));
        }

        bool isEmpty(int row, int col) {
            return (currBoard.at(row).at(col)->getName() == "None") ? true : false;
        }

        bool KingIsInCheck(char);

        void checkEnPassant(std::vector<int>, std::vector<int>);

        bool isEnPassantCapture(const std::vector<int>& sourceCoords, const std::vector<int>& destCoords) const {
            auto& piece = currBoard[sourceCoords[0]][sourceCoords[1]];
            if (!piece || piece->getName() != "Pawn") return false;
            
            return ((destCoords == EnPassantTargetCoords) && enPassantOppLast);
        }

        void ResetEnPassantVars() {
            EnPassantPieceToReplace.clear();
            EnPassantTargetCoords.clear();
            enPassantOpp = false;
            enPassantOppLast = false;
            enPassantAccepted = false;
        }

        // Only used for tests
        void setPiece(std::unique_ptr<Piece> p) {
            currBoard[p->getCoords().at(0)][p->getCoords().at(1)] = std::move(p);
        }

        struct castleVars {
            mutable bool wCastleLong = true;
            mutable bool wCastleShort = true;
            mutable bool bCastleLong = true;
            mutable bool bCastleShort = true;
            const std::vector<int> bKingCastleLongDest = {0,2};
            const std::vector<int> bKingCastleShortDest = {0,6};
            const std::vector<int> wKingCastleLongDest = {7,2};
            const std::vector<int> wKingCastleShortDest = {7,6};
            mutable std::vector<std::vector<int>> moveThroughCoords = {};
            mutable bool castleOpp = false;

        };
        castleVars castle;

        void updateCastleVars(const std::string& name, char colour, int column) {
            if ((name == "Rook") && (colour == 'w') && (column == 0) && (castle.wCastleLong)) {
                    castle.wCastleLong = false;
            } 
            else if ((name == "Rook") && (colour == 'w') && (column == 7) && (castle.wCastleShort)) {
                castle.wCastleShort = false;
            }
            else if ((name == "Rook") && (colour == 'b') && (column == 0) && (castle.bCastleLong)) {
                castle.bCastleLong = false;
            }
            else if ((name == "Rook") && (colour == 'b') && (column == 7) && (castle.bCastleShort)) {
                castle.bCastleShort = false;
            }
            else if ((name == "King") && (colour == 'w')) {
                castle.wCastleLong = castle.wCastleShort = false;
            }
            else if ((name == "King") && (colour == 'b')) {
                castle.bCastleLong = castle.bCastleShort = false;
            }
        }

        bool castlePathClear(char);
        void castleMoveRook(const std::vector<int>&);
        
};

#endif