#include "piece.h"
#include <vector>
#include <memory>
#include <iostream>
#include <string>
#include "pieces/empty.h"
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>

void Piece::setCoords(std::vector<int> destPos, std::vector<std::vector<std::shared_ptr<Piece>>>& board) {
    std::vector<int> currPos = getCoords();
    std::shared_ptr<Piece> tempPiece = board.at(currPos.at(0)).at(currPos.at(1));
    board.at(currPos.at(0)).at(currPos.at(1)) = std::make_shared<Empty>(currPos);
    board.at(destPos.at(0)).at(destPos.at(1)) = tempPiece;
}

void Piece::printPiece() {

}