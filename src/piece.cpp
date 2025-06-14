#include "piece.h"
#include <vector>
#include <memory>
#include <iostream>
#include <string>
#include "pieces/empty.h"
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include "helpers.h"

    Helpers::MoveContext Piece::getMoveContext(const std::vector<int>& destCoords) const {
        Helpers::MoveContext m;
        auto currCoords = getCoords();
        m.currRow = currCoords.at(0);
        m.currCol = currCoords.at(1);
        m.destRow = destCoords.at(0);
        m.destCol = destCoords.at(1);
        m.currColour = getColour();
        m.oppColour = (m.currColour == 'w') ? 'b' : 'w';
        return m;
    }