#ifndef _Piece_HPP
#define _Piece_HPP
#include <array>
#include <vector>
#include <SFML/Graphics.hpp>

using std::array;
using std::vector;

constexpr int BOARDLENGTH_INBLOCKS = 10;
constexpr int BOARDHEIGHT_INBLOCKS = 20;
constexpr float CELLSIZE = 40;

class Piece {
 public:
  vector<sf::Vector2f> blocks {4};
  sf::Vector2f origin;  // R
  sf::Color pieceColor;
  int PieceID, nextPieceID;

  Piece();
  bool canPieceMove(int board[][BOARDHEIGHT_INBLOCKS], int chx, int chy);
  void rotate();
  void drop(int board[][BOARDHEIGHT_INBLOCKS]);
  void drawPiece(int board[][BOARDHEIGHT_INBLOCKS], sf::RectangleShape cell);
};
#endif  // _Piece_HPP
