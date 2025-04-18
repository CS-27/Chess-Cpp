#ifndef KNIGHT_H
#define KNIGHT_H

#include "../piece.h"
#include <string>
#include <memory>

class Knight : public Piece {
    public:
        Knight(char c, std::vector<int>& v) : 
            Piece(c, "Knight", v.at(0), v.at(1)) {};

        virtual bool validMove(std::vector<int>, std::vector<std::vector<std::shared_ptr<Piece>>>&) override;
};

#endif