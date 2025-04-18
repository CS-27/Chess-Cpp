#ifndef BISHOP_H
#define BISHOP_H

#include "../piece.h"
#include <string>
#include <memory>

class Bishop : public Piece {
    public:
        Bishop(char c, std::vector<int>& v) : 
            Piece(c, "Bishop", v.at(0), v.at(1)) {};

            virtual bool validMove(std::vector<int>, std::vector<std::vector<std::shared_ptr<Piece>>>&) override;
};

#endif // BISHOP_H