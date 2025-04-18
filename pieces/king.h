#ifndef KING_H
#define KING_H

#include "../piece.h"
#include <string>
#include <memory>

class King : public Piece {
    public:
        King(char c, std::vector<int>& v) : 
            Piece(c, "King", v.at(0), v.at(1)) {};

        virtual bool validMove(std::vector<int>, std::vector<std::vector<std::shared_ptr<Piece>>>&) override {
            return false;
        }
};

#endif // KING_H