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
            colour(c), name(n), row(rw), col(cl), tx(t), img(tx) {display();};

        const char& getColour() {
            return colour;
        }
        const std::string& getName() {
            return name;
        }
        std::vector<int> getCoords() {
            return std::vector<int>{row, col};
        }

        const sf::Sprite& getSprite() {
            return img;
        }

        void display() {

            float desiredWidth = 80.f;
            float desiredHeight = 80.f;

            sf::Vector2u textureSize = tx.getSize();
            float scaleX = desiredWidth / textureSize.x;
            float scaleY = desiredHeight / textureSize.y;

            img.setScale(sf::Vector2f(scaleX, scaleY));

            float x = col * 80; //flipped due to board drawing logic
            float y = row * 80; //same
            img.setPosition(sf::Vector2f(x, y));

        }

        void setCoords(std::vector<int>, std::vector<std::vector<std::unique_ptr<Piece>>>&);

        void printPiece() {
            std::cout << this->colour << this->name << ": (" << this->row << ", " << this->col << ")\n";
        }

        virtual bool validMove(std::vector<int>, std::vector<std::vector<std::unique_ptr<Piece>>>&) = 0;

        /*void print() {
            desc = 
        }*/
};

#endif