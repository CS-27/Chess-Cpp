#ifndef PIECE_H
#define PIECE_H

#include <string>
#include <vector>
#include <memory>
#include <iostream>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>

class Piece {
    protected:
        char colour;
        std::string name;
        int row;
        int col;
        sf::Texture tx;
        sf::Sprite img;
    
    public:
        Piece(char c, std::string n, int rw, int cl, sf::Texture t = {}) : 
            colour(c), name(n), row(rw), col(cl), tx(t), img(tx) {};

        const char& getColour() {
            return colour;
        }
        const std::string& getName() {
            return name;
        }
        std::vector<int> getCoords() {
            return std::vector<int>{row, col};
        }

        sf::Sprite& getSprite() {
            return img;
        }

        sf::Texture& getTexture() {
            return tx;
        }

        void setCoords(const std::vector<int>& newCoords) {
            row = newCoords.at(0);
            col = newCoords.at(1);
        }

        void printPiece() {
            std::cout << this->colour << this->name << ": (" << this->row << ", " << this->col << ")\n";
        }

        virtual bool validMove(std::vector<int>, const std::vector<std::vector<std::unique_ptr<Piece>>>&) = 0;

        /*void print() {
            desc = 
        }*/
};

#endif