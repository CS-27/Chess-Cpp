#ifndef BISHOP_H
#define BISHOP_H

#include "../piece.h"
#include <string>
#include <memory>
#include <SFML/Graphics/Texture.hpp>

class Bishop : public Piece {
    public:
        Bishop(char c, std::vector<int>& v, sf::Texture t = {}) : 
            Piece(c, "Bishop", v.at(0), v.at(1), t) {};

            virtual bool validMove(std::vector<int>, std::vector<std::vector<std::unique_ptr<Piece>>>&) override;
};

#endif // BISHOP_H