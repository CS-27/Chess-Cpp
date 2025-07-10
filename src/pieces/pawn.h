#ifndef PAWN_H
#define PAWN_H

#include "../piece.h"
#include <string>
#include <memory>
#include <SFML/Graphics/Texture.hpp>

class Pawn : public Piece {

    public:
        Pawn(char c, const std::vector<int>& v, sf::Texture t = {}) : 
            Piece(c, "Pawn", v.at(0), v.at(1), t) {};

        virtual bool validMove(std::vector<int>, const Board& b) override;
};

#endif