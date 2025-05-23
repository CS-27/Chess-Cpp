#ifndef EMPTY_H
#define EMPTY_H

#include "../piece.h"
#include <string>
#include <memory>

class Empty : public Piece {
    public:
        Empty(std::vector<int>& v) : 
            Piece('_', "None", v.at(0), v.at(1)) {};

        virtual bool validMove(std::vector<int>, std::vector<std::vector<std::unique_ptr<Piece>>>&) override {
            return false;
        }
};

#endif