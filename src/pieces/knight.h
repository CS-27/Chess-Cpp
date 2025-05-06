#ifndef KNIGHT_H
#define KNIGHT_H

#include "../piece.h"
#include <string>
#include <memory>
#include <SFML/Graphics/Texture.hpp>

class Knight : public Piece {
    public:
        Knight(char c, std::vector<int>& v, sf::Texture t = {}) : 
            Piece(c, "Knight", v.at(0), v.at(1), t) {};

        virtual bool validMove(std::vector<int>, std::vector<std::vector<std::shared_ptr<Piece>>>&) override;
};

#endif