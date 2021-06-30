#ifndef _Piece_HPP
#define _Piece_HPP
#include <array>
#include <vector>
#include <SFML/Graphics.hpp>

using std::array;
using std::vector;

constexpr int BOARDLENGTH_INBLOCKS = 9;
constexpr int BOARDHEIGHT_INBLOCKS = 19;
constexpr float CELLSIZE = 40;

class Piece {
 public:
  vector<sf::Vector2f> blocks {4};
  sf::Vector2f origin;  // R
  sf::Color pieceColor;
  int PieceID, nextPieceID;

  Piece();
  Piece createNewPiece();
  bool canPieceMove(int board[][BOARDHEIGHT_INBLOCKS], int chx, int chy);
  void rotate();
  void drop(int board[][BOARDHEIGHT_INBLOCKS]);
  void drawPiece(sf::RectangleShape cell, sf::RenderWindow* window);
  void drawNextPiece(sf::RectangleShape nextcell, sf::RenderWindow* window);
};
#endif  // _Piece_HPP
