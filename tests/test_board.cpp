#include <catch2/catch_test_macros.hpp>
#include "board.h"
#include "piece.h"
#include "pieces/pawn.h"
#include "pieces/empty.h"
#include <memory>
#include <vector>

TEST_CASE("En Passant") {

    Board board;

    SECTION("Valid EP") {

        //white is at {3,4} for EP
        board.setPiece(std::make_unique<Pawn>('w', std::vector{3,4})); 
        
        // Set black pawn will try to move from {1,3} to {3,3}
        board.checkEnPassant(std::vector{1,3}, std::vector{3,3});
        REQUIRE(board.movePiece(std::vector{1,3}, std::vector{3,3}));
        board.enPassantOppLast = board.enPassantOpp;
        REQUIRE(board.movePiece(std::vector{3,4}, std::vector{2,3}));

        // Check that captured square is empty
        auto& captured = board.getPiece({3, 3});
        REQUIRE(captured->getName() == "None");
    }

    SECTION("Invalid EP") {
        
    }
}