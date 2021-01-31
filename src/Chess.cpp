#include "ChessKit/Chess.h"

#include <algorithm>
#include <cctype>


namespace ChessKit::Chess {

  namespace {
    auto index_from(Square square) -> std::size_t {
      return square.rank * 8 + square.file;
    }
  }

  auto to_string(Piece piece) -> std::string {
    switch(piece) {
      case Piece::Pawn: return "Pawn";
      case Piece::Rook: return "Rook";
      case Piece::Knight: return "Knight";
      case Piece::Bishop: return "Bishop";
      case Piece::Queen: return "Queen";
      case Piece::King: return "King";
    }
  }


  auto to_string(Player player) -> std::string {
    switch(player) {
      case Player::Black: return "Black";
      case Player::White: return "White";
    }
  }


  auto to_string(Square square) -> std::string {
    return "";
  }


  Position::Position()
      : player_(Player::White)
      , pieces_{
          { Player::White, {
              {Piece::Pawn,   0b00000000'11111111'00000000'00000000'00000000'00000000'00000000'00000000},
              {Piece::Rook,   0b10000001'00000000'00000000'00000000'00000000'00000000'00000000'00000000},
              {Piece::Knight, 0b01000010'00000000'00000000'00000000'00000000'00000000'00000000'00000000},
              {Piece::Bishop, 0b00100100'00000000'00000000'00000000'00000000'00000000'00000000'00000000},
              {Piece::Queen,  0b00010000'00000000'00000000'00000000'00000000'00000000'00000000'00000000},
              {Piece::King,   0b00001000'00000000'00000000'00000000'00000000'00000000'00000000'00000000},
          }},
          { Player::Black, {
              {Piece::Pawn,   0b00000000'00000000'00000000'00000000'00000000'00000000'11111111'00000000},
              {Piece::Rook,   0b00000000'00000000'00000000'00000000'00000000'00000000'00000000'10000001},
              {Piece::Knight, 0b00000000'00000000'00000000'00000000'00000000'00000000'00000000'01000010},
              {Piece::Bishop, 0b00000000'00000000'00000000'00000000'00000000'00000000'00000000'00100100},
              {Piece::Queen,  0b00000000'00000000'00000000'00000000'00000000'00000000'00000000'00010000},
              {Piece::King,   0b00000000'00000000'00000000'00000000'00000000'00000000'00000000'00001000},
          }},
      }{}

  
  auto Position::move(Move move) const -> std::optional<Position> {
    auto new_position = Position{*this};
    new_position.player_ = player_ == Player::White ? Player::Black : Player::White;

    auto const piece_at_from = piece_at(move.from);
    if (!piece_at_from.has_value()) {
      return std::nullopt;
    }

    auto const piece_at_to = piece_at(move.to);
    if (piece_at_to.has_value() && piece_at_to->player == player_) {
      return std::nullopt;
    }

    auto const from_idx = index_from(move.from);
    auto const to_idx = index_from(move.to);
    new_position.pieces_[player_][piece_at_from->piece][from_idx] = false;
    new_position.pieces_[player_][piece_at_from->piece][to_idx] = true;
    return new_position;
  }


  auto Position::piece_at(Square square) const -> std::optional<ColouredPiece> {
    using std::begin;
    using std::end;

    auto const square_index = index_from(square);

    for (auto player : pieces_) {    
      auto const it = std::find_if(
          begin(player.second), end(player.second),
          [square_index, this](auto const& p) { return p.second[square_index]; }
      );

      if (it != end(player.second)) {
        return ColouredPiece{player.first, it->first};
      }
    }

    return std::nullopt;
  }


  auto piece_from(char c) -> Piece {
    switch(std::tolower(c)) {
      case 'p': return Piece::Pawn;
      case 'r': return Piece::Rook;
      case 'n': return Piece::Knight;
      case 'b': return Piece::Bishop;
      case 'q': return Piece::Queen;
      case 'k': return Piece::King;
    }
    throw std::invalid_argument("unrecognised SAN notation for piece");
  }


  Position::Position(std::string_view FEN) {
    auto it = FEN.begin();
    for (auto rank = 7; rank > 0; --rank) {
      for (auto file = 0; file < 7; ++file) {
        if (std::isdigit(*it)) {
          auto const empty_squares = *it - '0';
          file += empty_squares - 1;
          ++it;
        }
        else if (std::isalpha(*it)) {
          auto const player = std::isupper(*it) ? Player::White : Player::Black;
          auto const piece = piece_from(*it);
          auto const square = Square{file, rank};
          pieces_[player][piece][index_from(square)] = true;
          ++it;
        }
        else {
          throw std::invalid_argument("invalid FEN notation");
        }
      }
      if (*it == '/') {
        ++it;
      }
    }

    if (*(++it) != ' ') {
      throw std::invalid_argument("invalid FEN notation");
    }

    player_ = *(++it) == 'w' ? Player::White : Player::Black;
  }
}