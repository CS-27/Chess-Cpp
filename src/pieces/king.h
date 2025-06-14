#ifndef KING_H
#define KING_H

#include "../piece.h"
#include <string>
#include <memory>
#include <SFML/Graphics/Texture.hpp>

class King : public Piece {
    public:
        King(char c, std::vector<int>& v, sf::Texture t = {}) : 
            Piece(c, "King", v.at(0), v.at(1), t) {};

        virtual bool validMove(std::vector<int>, const std::vector<std::vector<std::unique_ptr<Piece>>>&) override;

};

#endif // KING_H