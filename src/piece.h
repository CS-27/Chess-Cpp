#ifndef PIECE_H
#define PIECE_H

#include <string>
#include <vector>
#include <memory>
#include <iostream>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include "helpers.h"

// Forward declare Board
class Board;

class Piece {
    friend class Board;  // declare Board as a friend so it can access private/protected members

    protected:
        char colour;
        std::string name;
        int row;
        int col;
        sf::Texture tx;
        sf::Sprite img;

        Helpers::MoveContext getMoveContext(const std::vector<int>&) const;

        void setCoords(const std::vector<int>& newCoords) {
            row = newCoords.at(0);
            col = newCoords.at(1);
        }
    
    public:
        Piece(char c, std::string n, int rw, int cl, sf::Texture t = {}) : 
        colour(c), name(n), row(rw), col(cl), tx(t), img(tx) {};

        const char getColour() const {
            return colour;
        }
        const std::string& getName() const {
            return name;
        }
        std::vector<int> getCoords() const {
            return std::vector<int>{row, col};
        }

        sf::Sprite& getSprite() {
            return img;
        }

        sf::Texture& getTexture() {
            return tx;
        }

        void printPiece() const {
            std::cout << this->colour << this->name << ": (" << this->row << ", " << this->col << ")\n";
        }

        virtual bool validMove(std::vector<int>, const std::vector<std::vector<std::unique_ptr<Piece>>>&) = 0;

};

#endif