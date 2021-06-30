#include "Piece.hpp"

// x = col y = row
Piece::Piece() {
  // randomly generate a piece ID
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
    blocks.at(3).y = 3;
    origin.x = 0;
    origin.y = 1;
    pieceColor = sf::Color(50, 250, 0, 255);  // green
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
    pieceColor = sf::Color(230, 0, 0, 255);  // red
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
    origin.x = 0;
    origin.y = 1;
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
    origin.x = 0;
    origin.y = 1;
    pieceColor = sf::Color(255, 235, 20, 255);  // yellow
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
    pieceColor = sf::Color(23, 35, 200, 255);  // magenta
  }
  // O (square)
  if (PieceID == 5) {
    blocks.at(0).x = 0;   // x x o o
    blocks.at(0).y = 0;   // x x o o
    blocks.at(1).x = 0;   // o o o o
    blocks.at(1).y = 1;   // o o o o
    blocks.at(2).x = 1;
    blocks.at(2).y = 0;
    blocks.at(3).x = 1;
    blocks.at(3).y = 1;
    pieceColor = sf::Color(255, 135, 0, 255);  // orange
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
    origin.x = 0;
    origin.y = 1;
    pieceColor = sf::Color(5, 245, 245, 255);  // cyan
  }
}

// generate new pieces to to make and use the next piece
Piece Piece::createNewPiece() {
  Piece newPiece;
  return newPiece;
}

// collision detection
bool Piece::canPieceMove(int board[][BOARDHEIGHT_INBLOCKS], int chx, int chy) {
  bool canMove = true;

  // check if sides are in bounds and check if the space on the board is available
  for (int block = 0; block < 4; block++) {
    if ((blocks.at(block).x + chx < 0)
        || (blocks.at(block).x + chx > BOARDLENGTH_INBLOCKS)
        || (board[static_cast<int>(blocks.at(block).x + chx)][static_cast<int>(blocks.at(block).y)] == 1))
      canMove = false;

    // check row below is in bounds and check if the space on the board is available
    if ((blocks.at(block).y + chy < 0)
        || (blocks.at(block).y + chy > BOARDHEIGHT_INBLOCKS)
        || (board[static_cast<int>(blocks.at(block).x)][static_cast<int>(blocks.at(block).y + chy)] == 1))
      canMove = false;
  }
  return canMove;
}

void Piece::rotate() {
  if (PieceID == 5) return;
}

// place board at lowest possible open space
void Piece::drop(int board[][BOARDHEIGHT_INBLOCKS]) {
  bool canMoveDown = true;

  // find lowest row where space is empty
  while (canPieceMove(board, 0, 1) == true) {
    for (int block = 0; block < 4; block++) {
      blocks.at(block).y++;
    }
  }
}

// draw piece block by block on the board
void Piece::drawPiece(sf::RectangleShape cell, sf::RenderWindow* window) {
  cell.setFillColor(pieceColor);

  for (int block = 0; block < 4; block++) {
    cell.setPosition(blocks.at(block).x * CELLSIZE, blocks.at(block).y * CELLSIZE);
    window->draw(cell);
  }
}

// draw next piece block by block to the side of the board
void Piece::drawNextPiece(sf::RectangleShape nextcell, sf::RenderWindow* window) {
  nextcell.setFillColor(pieceColor);

  for (int block = 0; block < 4; block++) {
    nextcell.setPosition(blocks.at(block).x * CELLSIZE + 520, blocks.at(block).y * CELLSIZE + 280);
    window->draw(nextcell);
  }
}
