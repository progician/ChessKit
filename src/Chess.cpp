#include "ChessKit/Chess.h"

namespace ChessKit::Chess {

  auto to_string(Player player) -> std::string {
    switch(player) {
      case Player::White: return "White";
      case Player::Black: return "Black";
    }
  }

  Position::Position() : player_(Player::White) {}
}