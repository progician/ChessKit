#include "ChessKit/Chess.h"
#include "catch2/catch.hpp"

#include <ostream>

using namespace ChessKit::Chess;

namespace ChessKit::Chess {
  auto operator<<(std::ostream& ostr, Player player) -> std::ostream& {
    switch(player) {
      case Player::White:
        ostr << "White";
        break;
      case Player::Black:
        ostr << "Black";
        break;
    }

    return ostr;
  }


  auto operator<<(std::ostream& ostr, Piece piece) -> std::ostream& {
    ostr << to_string(piece);
    return ostr;
  }
}


TEST_CASE("White starts the game.") {
  REQUIRE(Position{}.turn() == Player::White);
}


TEST_CASE("Players take turns after each move.") {
  auto const pawn_to_e4 = Move{e2, e4};
  auto const position_after_first_move = Position{}.move(pawn_to_e4).value();

  REQUIRE(position_after_first_move.turn() == Player::Black);
}


TEST_CASE("If the move is legal, the `to` position will have piece `from` the from move.") {
  auto const pawn_to_e4 = Move{e2, e4};
  auto const position_after_first_move = Position{}.move(pawn_to_e4).value();

  REQUIRE(position_after_first_move.piece_at(e4).value() == ColouredPiece{Player::White, Piece::Pawn});
}


TEST_CASE("A position can be created using FEN notation") {
  // https://lichess.org/editor/8/8/3k4/4p3/4P3/5K2/8/8_b_-_-_0_1
  auto const ARBITRARY_FEN_POSITION = "8/8/3k4/4p3/4P3/5K2/8/8 b - - 0 1";
  auto const position_from_fen = Position{ARBITRARY_FEN_POSITION};
  REQUIRE(position_from_fen.turn() == Player::Black);
  REQUIRE(position_from_fen.piece_at(f3).value() == ColouredPiece{Player::White, Piece::King});
  REQUIRE(position_from_fen.piece_at(d6).value() == ColouredPiece{Player::Black, Piece::King});
}