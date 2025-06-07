#ifndef HELPERS_H
#define HELPERS_H

#include <vector>
#include <memory>
#include <map>
#include <iostream>
#include <string>
#include "piece.h"


namespace Helpers {

        struct MoveContext {
            int currRow, currCol;
            int destRow, destCol;
            char currColour, oppColour;
        };

        static void toggleTurn(char& turn) {
            turn = (turn == 'w') ? 'b' : 'w';
        }

        static bool canEnPassant();

        static bool cantMoveKing();

        static std::pair<int, int> get_coords(int pos_x, int pos_y) {
            // Due to the nature of the chess game in SFML we must flip these
            int x = pos_y / 80; 
            int y = pos_x / 80;
            return {x, y};
        }

};


#endif