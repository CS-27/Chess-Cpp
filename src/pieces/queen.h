#ifndef QUEEN_H
#define QUEEN_H

#include "../piece.h"
#include <string>
#include <memory>
#include "rook.h"
#include "bishop.h"
#include <SFML/Graphics/Texture.hpp>

class Queen : public Piece {
    public:
        Queen(char c, std::vector<int>& v, sf::Texture t = {}) : 
            Piece(c, "Queen", v.at(0), v.at(1), t) {};

        virtual bool validMove(std::vector<int> v, std::vector<std::vector<std::unique_ptr<Piece>>>& board) override {
            auto posVec = getCoords();
            auto tempBishop = std::make_unique<Bishop>(colour, posVec);
            auto tempRook = std::make_unique<Rook>(colour, posVec);
            return (tempBishop->validMove(v, board) || tempRook->validMove(v, board));
        }
};

#endif