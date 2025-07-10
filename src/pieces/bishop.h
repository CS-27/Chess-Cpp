#ifndef BISHOP_H
#define BISHOP_H

#include "../piece.h"
#include <string>
#include <memory>
#include <SFML/Graphics/Texture.hpp>

class Bishop : public Piece {
    public:
        Bishop(char c, const std::vector<int>& v, sf::Texture t = {}) : 
            Piece(c, "Bishop", v.at(0), v.at(1), t) {};

            virtual bool validMove(std::vector<int>, const Board& b) override;
};

#endif // BISHOP_H