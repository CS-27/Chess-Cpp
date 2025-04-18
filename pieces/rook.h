#ifndef ROOK_H
#define ROOK_H

#include "../piece.h"
#include <string>
#include <memory>

class Rook : public Piece {
    public:
        Rook(char c, std::vector<int>& v) : 
            Piece(c, "Rook", v.at(0), v.at(1)) {};

        virtual bool validMove(std::vector<int>, std::vector<std::vector<std::shared_ptr<Piece>>>&) override;
};

#endif