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

TEST_CASE("Castling") {

    Board board;

    SECTION("Valid Castle Short") {

        // Clear the path between rook and king
        for (const auto& v : std::vector<std::vector<int>>{{7,5},{7,6}}) {
            board.setPiece(std::make_unique<Empty>(v));
        }

        REQUIRE(board.movePiece(std::vector{7,4}, std::vector{7,6}));
        REQUIRE(board.getPiece({7,6})->getName() == "King");
        REQUIRE(board.getPiece({7,5})->getName() == "Rook");
        REQUIRE(board.getPiece({7,7})->getName() == "None");
        REQUIRE(board.getPiece({7,4})->getName() == "None");
        REQUIRE(board.castle.wCastleLong == false);
        REQUIRE(board.castle.wCastleShort == false);

    }

    SECTION("Valid Castle Long") {

        // Clear the path between rook and king
        for (const auto& v : std::vector<std::vector<int>>{{7,3},{7,2},{7,1}}) {
            board.setPiece(std::make_unique<Empty>(v));
        }

        REQUIRE(board.movePiece(std::vector{7,4}, std::vector{7,2}));
        REQUIRE(board.getPiece({7,2})->getName() == "King");
        REQUIRE(board.getPiece({7,3})->getName() == "Rook");
        REQUIRE(board.getPiece({7,4})->getName() == "None");
        REQUIRE(board.getPiece({7,1})->getName() == "None");
        REQUIRE(board.getPiece({7,0})->getName() == "None");
        REQUIRE(board.castle.wCastleLong == false);
        REQUIRE(board.castle.wCastleShort == false);

    }

    SECTION("Invalid castle after king move") {

        // Clear the path between rook and king
        for (const auto& v : std::vector<std::vector<int>>{{7,3},{7,2},{7,1}}) {
            board.setPiece(std::make_unique<Empty>(v));
        }

        REQUIRE(board.movePiece(std::vector{7,4}, std::vector{7,3}));
        REQUIRE(board.movePiece(std::vector{7,3}, std::vector{7,4}));
        REQUIRE(!board.movePiece(std::vector{7,4}, std::vector{7,2}));
        REQUIRE(board.getPiece({7,4})->getName() == "King");
        REQUIRE(board.getPiece({7,0})->getName() == "Rook");
        REQUIRE(board.getPiece({7,3})->getName() == "None");
        REQUIRE(board.getPiece({7,2})->getName() == "None");
        REQUIRE(board.getPiece({7,1})->getName() == "None");
        REQUIRE(board.castle.wCastleLong == false);
        REQUIRE(board.castle.wCastleShort == false);
    }

    SECTION("Invalid castle after rook move") {

        // Clear the path between rook and king
        for (const auto& v : std::vector<std::vector<int>>{{7,3},{7,2},{7,1}}) {
            board.setPiece(std::make_unique<Empty>(v));
        }

        REQUIRE(board.movePiece(std::vector{7,0}, std::vector{7,1}));
        REQUIRE(board.castle.wCastleLong == false);
        REQUIRE(board.castle.wCastleShort == true);
        REQUIRE(board.movePiece(std::vector{7,1}, std::vector{7,0}));
        REQUIRE(!board.movePiece(std::vector{7,4}, std::vector{7,2}));
        REQUIRE(board.getPiece({7,4})->getName() == "King");
        REQUIRE(board.getPiece({7,0})->getName() == "Rook");
        REQUIRE(board.getPiece({7,3})->getName() == "None");
        REQUIRE(board.getPiece({7,2})->getName() == "None");
        REQUIRE(board.getPiece({7,1})->getName() == "None");
        REQUIRE(board.castle.wCastleLong == false);
        REQUIRE(board.castle.wCastleShort == true);
    }

    SECTION("Can't castle through check") {

        // Clear the path between rook and king
        for (const auto& v : std::vector<std::vector<int>>{{7,3},{7,2},{7,1}}) {
            board.setPiece(std::make_unique<Empty>(v));
        }

        // put enemy rook on {6,2}
        board.setPiece(std::make_unique<Rook>('b', std::vector<int>{6,2}));

        REQUIRE(!board.movePiece(std::vector{7,4}, std::vector{7,2}));
        REQUIRE(board.getPiece({7,4})->getName() == "King");
        REQUIRE(board.getPiece({7,0})->getName() == "Rook");
        REQUIRE(board.getPiece({7,3})->getName() == "None");
        REQUIRE(board.getPiece({7,2})->getName() == "None");
        REQUIRE(board.getPiece({7,1})->getName() == "None");
        REQUIRE(board.castle.wCastleLong == true);
        REQUIRE(board.castle.wCastleShort == true);
    }

}