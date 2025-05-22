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

Board::Board() : currBoard(std::vector(8, std::vector<std::shared_ptr<Piece>>(8))) {
    for (int i = 0; i<8; i++) {
        for (int j = 0; j<8; j++) {
            auto v = std::vector<int>{i, j};
            if (i == 0) {
                if (j == 0 || j == 7) {
                    sf::Texture brT;
                    brT.loadFromFile("assets/br.png");
                    auto bRook = std::make_shared<Rook>('b', v, brT);
                    currBoard[i][j] = bRook;
                }
                else if (j == 1 || j == 6) {
                    sf::Texture bnT;
                    bnT.loadFromFile("assets/bn.png");
                    auto bKnight = std::make_shared<Knight>('b', v, bnT);
                    currBoard[i][j] = bKnight;
                }
                else if (j == 2 || j == 5) {
                    sf::Texture bbT;
                    bbT.loadFromFile("assets/bb.png");
                    auto bBishop = std::make_shared<Bishop>('b', v, bbT);
                    currBoard[i][j] = bBishop;
                }
                else if (j == 3) {
                    sf::Texture bqT;
                    bqT.loadFromFile("assets/bq.png");
                    auto bQueen = std::make_shared<Queen>('b', v, bqT);
                    currBoard[i][j] = bQueen;
                }
                else if (j == 4) {
                    sf::Texture bkT;
                    bkT.loadFromFile("assets/bk.png");
                    auto bKing = std::make_shared<King>('b', v, bkT);
                    currBoard[i][j] = bKing;
                }
            }
            else if (i == 1) {
                sf::Texture bpT;
                bpT.loadFromFile("assets/bp.png");
                auto bPawn = std::make_shared<Pawn>('b', v, bpT);
                currBoard[i][j] = bPawn;
            }
            else if (i == 7) {
                if (j == 0 || j == 7) {
                    sf::Texture wrT;
                    wrT.loadFromFile("assets/wr.png");
                    auto wRook = std::make_shared<Rook>('w', v, wrT);
                    currBoard[i][j] = wRook;
                }
                else if (j == 1 || j == 6) {
                    sf::Texture wnT;
                    wnT.loadFromFile("assets/wn.png");
                    auto wKnight = std::make_shared<Knight>('w', v, wnT);
                    currBoard[i][j] = wKnight;
                }
                else if (j == 2 || j == 5) {
                    sf::Texture wbT;
                    wbT.loadFromFile("assets/wb.png");
                    auto wBishop = std::make_shared<Bishop>('w', v, wbT);
                    currBoard[i][j] = wBishop;
                }
                else if (j == 3) {
                    sf::Texture wqT;
                    wqT.loadFromFile("assets/wq.png");
                    auto wQueen = std::make_shared<Queen>('w', v, wqT);
                    currBoard[i][j] = wQueen;
                }
                else if (j == 4) {
                    sf::Texture wkT;
                    wkT.loadFromFile("assets/wk.png");
                    auto wKing = std::make_shared<King>('w', v, wkT);
                    currBoard[i][j] = wKing;
                }
            }
            else if (i == 6) {
                sf::Texture wpT;
                wpT.loadFromFile("assets/wp.png");
                auto wPawn = std::make_shared<Pawn>('w', v, wpT);
                currBoard[i][j] = wPawn;
            }
            else {
                currBoard[i][j] = std::make_shared<Empty>(v);
            }
        }
    }
    /*for (int i = 0; i < currBoard.size(); i++) {
        std::cout << "{";
        for (int j = 0; j < currBoard.at(0).size(); j++) {
        //std::cout << i << ", " << j << std::endl;
        std::cout << currBoard.at(i).at(j)->getColour() << currBoard.at(i).at(j)->getName() << ", ";
        }
        std::cout << "}" << std::endl;
    }*/
}

void Board::printBoard(std::vector<std::vector<std::shared_ptr<Piece>>>& board) const {
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