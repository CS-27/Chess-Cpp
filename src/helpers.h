#ifndef HELPERS_H
#define HELPERS_H

#include <vector>
#include <memory>
#include <map>
#include <iostream>
#include <string>
#include "piece.h"


class Helpers {
    public:
        /*static void updateBoard(std::unique_ptr<Piece>& p, std::vector<int> startPos, std::vector<int> endPos) {
        }*/

        static void toggleTurn(char& turn) {
            turn == 'w' ? turn = 'b' : turn = 'w';
        }

        static bool isCheck(
                std::unique_ptr<Piece>& p, 
                std::vector<int> destPos, 
                std::vector<std::vector<std::unique_ptr<Piece>>>& board);

        static bool canEnPassant();

        static bool cantMoveKing();

        static std::vector<std::vector<int>> takeInput(char turn) {
            std::vector<std::vector<int>> soln;
            std::map<char, int> letterToNum = {{'a', 7}, {'b', 6}, {'c', 5}, {'d', 4}, {'e', 3}, {'f', 2}, {'g', 1}, {'h', 0}};
            (turn == 'w') ? std::cout << "White to move, " : std::cout << "Black to move, ";
            std::cout << "enter the square of the piece you would like to move (i.e a1): " << std::endl;
            std::string startPosStr;
            std::cin >> startPosStr;
            std::cout << "enter the square you would like to move the piece to (i.e h8): " << std::endl;
            std::string endPosStr;
            std::cin >> endPosStr;
            int startRow;
            int startCol;
            int endRow;
            int endCol;
            startRow = letterToNum.at(startPosStr.at(0));
            startCol = std::stoi(std::string(1, startPosStr.at(1))) - 1;
            auto start = std::vector<int>{startRow, startCol};
            soln.push_back(start);
            endRow = letterToNum.at(endPosStr.at(0));
            endCol = std::stoi(std::string(1, endPosStr.at(1))) - 1;
            auto end = std::vector<int>{endRow, endCol};
            soln.push_back(end);
            return soln;
        }

        static void movePiece(std::vector<int> start, std::vector<int> end, std::unique_ptr<Piece> &p) {};

        static std::pair<int, int> get_coords(int pos_x, int pos_y) {
            // Due to the nature of the chess game in SFML we must flip these
            int x = pos_y / 80; 
            int y = pos_x / 80;
            return {x, y};
        }

};


#endif