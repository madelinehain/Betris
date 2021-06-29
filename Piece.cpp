#include "Piece.hpp"

Piece::Piece() {
  PieceID = rand() % 7;
  // I (straight)
  if (PieceID == 0) {
    blocks.at(0).x = 0;  // x o o o
    blocks.at(0).y = 0;  // R o o o
    blocks.at(1).x = 0;  // x o o o
    blocks.at(1).y = 1;  // x o o o
    blocks.at(2).x = 0;
    blocks.at(2).y = 2;
    blocks.at(3).x = 0;
    blocks.at(3).x = 3;
    origin.x = 1;
    origin.y = 0;
    pieceColor = sf::Color::Green;
  }
  // Z
  if (PieceID == 1) {
    blocks.at(0).x = 0;   // x o o o
    blocks.at(0).y = 0;   // R x o o
    blocks.at(1).x = 0;   // o x o o
    blocks.at(1).y = 1;   // o o o o
    blocks.at(2).x = 1;
    blocks.at(2).y = 1;
    blocks.at(3).x = 1;
    blocks.at(3).y = 2;
    origin.x = 0;
    origin.y = 1;
    pieceColor = sf::Color::Red;
  }
  // S (reverse Z)
  if (PieceID == 2) {
    blocks.at(0).x = 1;   // o x o o
    blocks.at(0).y = 0;   // R x o o
    blocks.at(1).x = 0;   // x o o o
    blocks.at(1).y = 1;   // o o o o
    blocks.at(2).x = 1;
    blocks.at(2).y = 1;
    blocks.at(3).x = 0;
    blocks.at(3).y = 2;
    origin.x = 1;
    origin.y = 0;
    pieceColor = sf::Color::Blue;
  }
  // L
  if (PieceID == 3) {
    blocks.at(0).x = 0;   // x o o o
    blocks.at(0).y = 0;   // R o o o
    blocks.at(1).x = 0;   // x x o o
    blocks.at(1).y = 1;   // o o o o
    blocks.at(2).x = 0;
    blocks.at(2).y = 2;
    blocks.at(3).x = 1;
    blocks.at(3).y = 2;
    origin.x = 1;
    origin.y = 0;
    pieceColor = sf::Color::Yellow;
  }
  // J (reverse L)
  if (PieceID == 4) {
    blocks.at(0).x = 1;   // o x o o
    blocks.at(0).y = 0;   // o R o o
    blocks.at(1).x = 1;   // x x o o
    blocks.at(1).y = 1;   // o o o o
    blocks.at(2).x = 0;
    blocks.at(2).y = 2;
    blocks.at(2).x = 1;
    blocks.at(3).y = 2;
    origin.x = 1;
    origin.y = 1;
    pieceColor = sf::Color::Magenta;
  }
  // O (square)
  if (PieceID == 5) {
    blocks.at(0).x = 0;   // x x o o
    blocks.at(0).y = 0;   // x x o o
    blocks.at(1).x = 0;   // o o o o
    blocks.at(1).y = 1;   // o o o o
    blocks.at(2).x = 1;
    blocks.at(2).y - 0;
    blocks.at(3).x = 1;
    blocks.at(3).y = 1;
    pieceColor = sf::Color(120, 20, 170, 100);
  }
  // T
  if (PieceID == 6) {
    blocks.at(0).x = 0;
    blocks.at(0).y = 0;   // x o o o
    blocks.at(1).x = 0;   // R x o o
    blocks.at(1).y = 1;   // x o o o
    blocks.at(2).x = 1;   // o o o o
    blocks.at(2).y = 1;
    blocks.at(3).x = 0;
    blocks.at(3).y = 2;
    origin.x = 1;
    origin.y = 0;
    pieceColor = sf::Color::Cyan;
  }
}
bool Piece::canPieceMove(int board[][BOARDLENGTH_INBLOCKS], int chx, int chy) {
  bool canMove = true;
  for (int i = 0; i < 4; i++) {
    // check left and right
    if ((blocks.at(i).x + chx < 0)
      || (blocks.at(i).x + chx > BOARDLENGTH_INBLOCKS)
      || (board[static_cast<int>(blocks.at(i).x + chx)][static_cast<int>(blocks.at(i).y)] == 1))
      canMove = false;
    // check down
    if ((blocks.at(i).y + chy < 0)
      || (blocks.at(i).y + chy > BOARDHEIGHT_INBLOCKS)
      || (board[static_cast<int>(blocks.at(i).x)][static_cast<int>(blocks.at(i).y + chy)] == 1))
      canMove = false;
  }
  return canMove;
}

void Piece::rotate() {
  if (PieceID == 5) return;
}

void Piece::drop() {}
