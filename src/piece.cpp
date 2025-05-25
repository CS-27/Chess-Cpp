#include "piece.h"
#include <vector>
#include <memory>
#include <iostream>
#include <string>
#include "pieces/empty.h"
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>

void Piece::setCoords(std::vector<int> destPos, std::vector<std::vector<std::unique_ptr<Piece>>>& board) {
    std::vector<int> currPos = getCoords();

    // Move the piece from current position to destination
    board.at(destPos.at(0)).at(destPos.at(1)) = std::move(board.at(currPos.at(0)).at(currPos.at(1)));

    // Place a new Empty piece in the original position
    board.at(currPos.at(0)).at(currPos.at(1)) = std::make_unique<Empty>(currPos);
}