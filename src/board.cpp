#include "board.h"
#include "piece.h"
#include "pieces/rook.h"
#include "pieces/knight.h"
#include "pieces/bishop.h"
#include "pieces/king.h"
#include "pieces/queen.h"
#include "pieces/pawn.h"
#include "pieces/empty.h"
#include <iostream>
#include <vector>
#include <memory>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>

Board::Board() {

    currBoard.resize(8);
    for (auto& row : currBoard) {
        row.resize(8);
    }

    for (int i = 0; i<8; i++) {
        for (int j = 0; j<8; j++) {
            auto v = std::vector<int>{i, j};
            if (i == 0) {
                if (j == 0 || j == 7) {
                    sf::Texture brT;
                    brT.loadFromFile("assets/br.png");
                    currBoard[i][j] = std::make_unique<Rook>('b', v, brT);
                }
                else if (j == 1 || j == 6) {
                    sf::Texture bnT;
                    bnT.loadFromFile("assets/bn.png");
                    currBoard[i][j] = std::make_unique<Knight>('b', v, bnT);
                }
                else if (j == 2 || j == 5) {
                    sf::Texture bbT;
                    bbT.loadFromFile("assets/bb.png");
                    currBoard[i][j] = std::make_unique<Bishop>('b', v, bbT);
                }
                else if (j == 3) {
                    sf::Texture bqT;
                    bqT.loadFromFile("assets/bq.png");
                    currBoard[i][j] = std::make_unique<Queen>('b', v, bqT);
                }
                else if (j == 4) {
                    sf::Texture bkT;
                    bkT.loadFromFile("assets/bk.png");
                    currBoard[i][j] = std::make_unique<King>('b', v, bkT);
                }
            }
            else if (i == 1) {
                sf::Texture bpT;
                bpT.loadFromFile("assets/bp.png");
                currBoard[i][j] = std::make_unique<Pawn>('b', v, bpT);
            }
            else if (i == 7) {
                if (j == 0 || j == 7) {
                    sf::Texture wrT;
                    wrT.loadFromFile("assets/wr.png");
                    currBoard[i][j] = std::make_unique<Rook>('w', v, wrT);
                }
                else if (j == 1 || j == 6) {
                    sf::Texture wnT;
                    wnT.loadFromFile("assets/wn.png");
                    currBoard[i][j] = std::make_unique<Knight>('w', v, wnT);
                }
                else if (j == 2 || j == 5) {
                    sf::Texture wbT;
                    wbT.loadFromFile("assets/wb.png");
                    currBoard[i][j] = std::make_unique<Bishop>('w', v, wbT);
                }
                else if (j == 3) {
                    sf::Texture wqT;
                    wqT.loadFromFile("assets/wq.png");
                    currBoard[i][j] = std::make_unique<Queen>('w', v, wqT);
                }
                else if (j == 4) {
                    sf::Texture wkT;
                    wkT.loadFromFile("assets/wk.png");
                    currBoard[i][j] = std::make_unique<King>('w', v, wkT);
                }
            }
            else if (i == 6) {
                sf::Texture wpT;
                wpT.loadFromFile("assets/wp.png");
                currBoard[i][j] = std::make_unique<Pawn>('w', v, wpT);
            }
            else {
                currBoard[i][j] = std::make_unique<Empty>(v);
            }
        }
    }
}

void Board::printBoard(std::vector<std::vector<std::unique_ptr<Piece>>>& board) const {
    int buffer = 8;
    for (int i = 0; i < board.size(); i++) {
        std::cout << "{";
        for (int j = 0; j < board.at(0).size(); j++) {
            //std::cout << i << ", " << j << std::endl;
            std::string name = board.at(i).at(j)->getName();
            if (name == "None") {
                name = "____";
            }
            std::cout << board.at(i).at(j)->getColour() << name;
            int addOn = buffer - name.size();
            for(int x = 0; x < addOn; x++) {
                std::cout << " ";
            }
            if (j < board.at(0).size()-1) {
                std::cout << ", ";
            }
        }
        std::cout << "}" << std::endl;
    }
}

bool Board::movePiece(const std::vector<int>& sourceCoords, const std::vector<int>& destCoords) {
    auto& sourcePiece = currBoard[sourceCoords[0]][sourceCoords[1]];
    auto& sourceName = sourcePiece->getName();
    auto sourceColour = sourcePiece->getColour();

    if (!sourcePiece->validMove(destCoords, *this)) {
        std::cout << "invalid move\n";
        return false;
    }  

    if (castle.castleOpp) {
        if (!castlePathClear((sourceColour == 'b') ? 'w' : 'b')) {
            castle.castleOpp = false;
            castle.moveThroughCoords.clear();
            if (destCoords.at(1) == 2 && sourceColour == 'b') {
                castle.bCastleLong = true;
            }
            if (destCoords.at(1) == 2 && sourceColour == 'w') {
                castle.wCastleLong = true;
            }
            if (destCoords.at(1) == 6 && sourceColour == 'b') {
                castle.bCastleShort = true;
            }
            if (destCoords.at(1) == 6 && sourceColour == 'w') {
                castle.wCastleShort = true;
            }
            std::cout << "invalid move, king's castle path is not clear\n";
            return false;
        }
        else {
            castleMoveRook(destCoords);
            castle.castleOpp = false;
            castle.moveThroughCoords.clear();
        }
    }


    std::unique_ptr<Piece> EnPassantBackup;
    bool isEP = isEnPassantCapture(sourceCoords, destCoords);
    if (isEP) {
        // Remove the captured pawn behind the destination
        EnPassantBackup = std::move(currBoard[EnPassantPieceToReplace.at(0)][EnPassantPieceToReplace.at(1)]);
        currBoard[EnPassantPieceToReplace.at(0)][EnPassantPieceToReplace.at(1)] = std::make_unique<Empty>(EnPassantPieceToReplace);
        std::cout << "En passant capture executed\n";
    }

    // Backup pieces
    auto backupSource = std::move(currBoard[sourceCoords[0]][sourceCoords[1]]);
    auto backupDest = std::move(currBoard[destCoords[0]][destCoords[1]]);

    // Simulate move
    currBoard[destCoords[0]][destCoords[1]] = std::move(backupSource);
    currBoard[destCoords[0]][destCoords[1]]->setCoords(destCoords);
    currBoard[sourceCoords[0]][sourceCoords[1]] = std::make_unique<Empty>(sourceCoords);

    // Check if own king is in check after move
    if (!castle.castleOpp && KingIsInCheck(currBoard[destCoords[0]][destCoords[1]]->getColour())) {
        // Revert the move
        currBoard[sourceCoords[0]][sourceCoords[1]] = std::move(currBoard[destCoords[0]][destCoords[1]]);
        currBoard[sourceCoords[0]][sourceCoords[1]]->setCoords(sourceCoords);
        currBoard[destCoords[0]][destCoords[1]] = std::move(backupDest);
        
        if (isEP) {
            currBoard[EnPassantPieceToReplace.at(0)][EnPassantPieceToReplace.at(1)] = std::move(EnPassantBackup);
        }

        std::cout << "invalid move, king in check after move\n";
        return false;
    }

    if (!enPassantOpp) {
        ResetEnPassantVars();
    }

    updateCastleVars(sourceName, sourceColour, sourceCoords[1]);

    std::cout << "valid move\n";
    return true;
}

bool Board::KingIsInCheck(char kingColour) {
    int kingRow = -1, kingCol = -1;

    // Find the king's position
    for (int row = 0; row < 8; ++row) {
        for (int col = 0; col < 8; ++col) {
            auto& piece = currBoard[row][col];
            if (piece && piece->getName() == "King" && piece->getColour() == kingColour) {
                kingRow = row;
                kingCol = col;
                break;
            }
        }
    }

    if (kingRow == -1 || kingCol == -1) {
        throw std::runtime_error("King not found on board");
    }

    // Check if any opponent piece can move to the king's position
    for (int row = 0; row < 8; ++row) {
        for (int col = 0; col < 8; ++col) {
            auto& piece = currBoard[row][col];
            if (piece && piece->getColour() != kingColour && piece->getColour() != '_') {
                if (piece->validMove({kingRow, kingCol}, *this)) {
                    return true;
                }
            }
        }
    }

    return false;
}

void Board::checkEnPassant(std::vector<int> source, std::vector<int> dest) {
    auto& sourcePiece = currBoard.at(source.at(0)).at(source.at(1));
    if (sourcePiece->getName() == "Pawn") {
        int enPassantCol = (sourcePiece->getColour() == 'w') ? 6 : 1;
        if ((std::abs(dest.at(0) - source.at(0)) == 2) && source.at(0) == enPassantCol) {
            enPassantOpp = true;
            EnPassantPieceToReplace = dest;
            EnPassantTargetCoords = std::vector<int>{(sourcePiece->getColour() == 'w') ? 5 : 2, dest.at(1)};
            return;
        }
    }
    enPassantOpp = false;
}

bool Board::castlePathClear(char enemyColour) {

    // Check if any opponent piece can move to the king's position
    for (int row = 0; row < 8; ++row) {
        for (int col = 0; col < 8; ++col) {
            auto& piece = currBoard[row][col];
            if (piece && piece->getColour() == enemyColour) {
                for (const auto& v : castle.moveThroughCoords) {
                    if (!(currBoard.at(v.at(0)).at(v.at(1))->getName() == "None")
                        && !(currBoard.at(v.at(0)).at(v.at(1))->getName() == "King" && 
                        currBoard.at(v.at(0)).at(v.at(1))->getColour() != enemyColour)) {
                        return false;
                    }
                    if (piece->validMove({v.at(0), v.at(1)}, *this)) {
                        return false;
                    }
                }
            }
        }
    }

    return true;
}

void Board::castleMoveRook(const std::vector<int>& dest) {
    int rookDestCol, rookSourceCol;
    if (dest.at(1) == 2) {
        rookDestCol = 3;
        rookSourceCol = 0;
    }
    else if (dest.at(1) == 6) {
        rookDestCol = 5;
        rookSourceCol = 7;
    }
    currBoard.at(dest.at(0)).at(rookDestCol) = std::move(currBoard.at(dest.at(0)).at(rookSourceCol));
    currBoard.at(dest.at(0)).at(rookDestCol)->setCoords(std::vector<int>{dest.at(0),rookDestCol});
    auto tempvec = std::vector<int>{dest.at(0), rookSourceCol};
    currBoard.at(dest.at(0)).at(rookSourceCol) = std::make_unique<Empty>(tempvec);
}
