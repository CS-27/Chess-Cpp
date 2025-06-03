#ifndef ROOK_H
#define ROOK_H

#include "../piece.h"
#include <string>
#include <memory>
#include <SFML/Graphics/Texture.hpp>

class Rook : public Piece {
    public:
        Rook(char c, std::vector<int>& v, sf::Texture t = {}) : 
            Piece(c, "Rook", v.at(0), v.at(1), t) {};

        virtual bool validMove(std::vector<int>, const std::vector<std::vector<std::unique_ptr<Piece>>>&) override;
};

#endif