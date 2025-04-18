#ifndef PAWN_H
#define PAWN_H

#include "../piece.h"
#include <string>
#include <memory>

class Pawn : public Piece {
    public:
        Pawn(char c, std::vector<int>& v) : 
            Piece(c, "Pawn", v.at(0), v.at(1)) {};

        virtual bool validMove(std::vector<int>, std::vector<std::vector<std::shared_ptr<Piece>>>&) override;
};

#endif