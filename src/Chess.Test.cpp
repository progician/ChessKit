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
  auto const initial_position = Position{};
  REQUIRE(initial_position.turn() == Player::White);
}


TEST_CASE("Players take turns after each move.") {
  auto const initial_position = Position{};
  auto const pawn_to_e5 = Move{e2, e5};

  auto const position_after_first_move = initial_position.move(pawn_to_e5).value();

  REQUIRE(position_after_first_move.turn() == Player::Black);
}


TEST_CASE("If the move is legal, the two position will have piece from the from move.") {
  auto const initial_position = Position{};
  auto const pawn_to_e5 = Move{e2, e5};

  auto const position_after_first_move = initial_position.move(pawn_to_e5).value();

  REQUIRE(position_after_first_move.piece_at(e5).value() == ColouredPiece{Player::White, Piece::Pawn});
}
