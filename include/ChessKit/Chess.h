#pragma once

#include <vector>
#include <string>
#include <optional>
#include <bitset>
#include <map>

namespace ChessKit::Chess {
  enum class Player {
    White,
    Black,
  };
  auto to_string(Player) -> std::string;

  class Position {
    Player player_;
  public:
    Position();

    auto turn() const -> Player { return player_; }
  };
}