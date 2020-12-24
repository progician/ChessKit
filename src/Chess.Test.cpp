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
}


TEST_CASE("White starts the game.") {
  auto const initial_position = Position{};
  REQUIRE(initial_position.turn() == Player::White);
}