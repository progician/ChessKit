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


  enum class Piece {
    Pawn,
    Rook,
    Knight,
    Bishop,
    Queen,
    King,
  };
  auto to_string(Piece) -> std::string;


  struct Square {
    int const file;
    int const rank;
  };

  constexpr Square a1 = {0, 0};
  constexpr Square a2 = {0, 1};
  constexpr Square a3 = {0, 2};
  constexpr Square a4 = {0, 3};
  constexpr Square a5 = {0, 4};
  constexpr Square a6 = {0, 5};
  constexpr Square a7 = {0, 6};
  constexpr Square b1 = {1, 0};
  constexpr Square b2 = {1, 1};
  constexpr Square b3 = {1, 2};
  constexpr Square b4 = {1, 3};
  constexpr Square b5 = {1, 4};
  constexpr Square b6 = {1, 5};
  constexpr Square b7 = {1, 6};
  constexpr Square c1 = {2, 0};
  constexpr Square c2 = {2, 1};
  constexpr Square c3 = {2, 2};
  constexpr Square c4 = {2, 3};
  constexpr Square c5 = {2, 4};
  constexpr Square c6 = {2, 5};
  constexpr Square c7 = {2, 6};
  constexpr Square d1 = {3, 0};
  constexpr Square d2 = {3, 1};
  constexpr Square d3 = {3, 2};
  constexpr Square d4 = {3, 3};
  constexpr Square d5 = {3, 4};
  constexpr Square d6 = {3, 5};
  constexpr Square d7 = {3, 6};
  constexpr Square e1 = {4, 0};
  constexpr Square e2 = {4, 1};
  constexpr Square e3 = {4, 2};
  constexpr Square e4 = {4, 3};
  constexpr Square e5 = {4, 4};
  constexpr Square e6 = {4, 5};
  constexpr Square e7 = {4, 6};
  constexpr Square f1 = {5, 0};
  constexpr Square f2 = {5, 1};
  constexpr Square f3 = {5, 2};
  constexpr Square f4 = {5, 3};
  constexpr Square f5 = {5, 4};
  constexpr Square f6 = {5, 5};
  constexpr Square f7 = {5, 6};
  constexpr Square g1 = {6, 0};
  constexpr Square g2 = {6, 1};
  constexpr Square g3 = {6, 2};
  constexpr Square g4 = {6, 3};
  constexpr Square g5 = {6, 4};
  constexpr Square g6 = {6, 5};
  constexpr Square g7 = {6, 6};
  constexpr Square h1 = {7, 0};
  constexpr Square h2 = {7, 1};
  constexpr Square h3 = {7, 2};
  constexpr Square h4 = {7, 3};
  constexpr Square h5 = {7, 4};
  constexpr Square h6 = {7, 5};
  constexpr Square h7 = {7, 6};

  auto to_string(Square) -> std::string;

  struct Move {
    Square from;
    Square to;
  };


  struct ColouredPiece {
    Player const player;
    Piece const piece;
  };
  inline auto operator==(ColouredPiece const& lhs, ColouredPiece const& rhs) -> bool {
    return lhs.player == rhs.player && lhs.piece == rhs.piece;
  }


  using Moves = std::vector<Move>;


  class Position {
    Player player_;

    using BitBoard = std::bitset<64>;
    using Pieces = std::map<Piece, BitBoard>;
    std::map<Player, Pieces> pieces_;

  public:
    Position();

    auto move(Move) const -> std::optional<Position>;

    auto available_moves() const -> Moves;
    auto turn() const -> Player { return player_; }
    auto piece_at(Square) const -> std::optional<ColouredPiece>;
  };
}