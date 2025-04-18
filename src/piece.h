#ifndef PIECE_H
#define PIECE_H

#include <string>
#include <vector>
#include <memory>
#include <iostream>

class Piece {
    protected:
        char colour;
        std::string name;
        int row;
        int col;
    
    public:
        Piece(char c, std::string n, int rw, int cl) : 
            colour(c), name(n), row(rw), col(cl) {};

        const char& getColour() {
            return colour;
        }
        const std::string& getName() {
            return name;
        }
        std::vector<int> getCoords() {
            return std::vector<int>{row, col};
        }

        void setCoords(std::vector<int>, std::vector<std::vector<std::shared_ptr<Piece>>>&);

        void printPiece();

        virtual bool validMove(std::vector<int>, std::vector<std::vector<std::shared_ptr<Piece>>>&) = 0;

        /*void print() {
            desc = 
        }*/
};

#endif