#include "boardStruct.hpp"
#include <vector>


// Board initializer with invisible blocks
Board::Board() {
  vector<vector<Block>> content(BOARDR, vector<Block>
                                (BOARDC, Block(sf::Color::Transparent, false)));
  board = content;
  boardWeight = 0;

  for (int i = 0; i < BOARDC; i++) r.push_back(i);
  for (int i = 0; i < BOARDR; i++) c.push_back(i);
}

bool Board::isGameOver() {
  for (int i = 0; i < BOARDC; i++) {
    if (board.at(0).at(i).isVisible) return true;
  }
  return false;
}

void Board::draw(sf::RenderWindow * window) {
  for (int r = 0; r < BOARDR; r++) {
    for (int c = 0; c < BOARDC; c++) {
      if (board.at(r).at(c).isVisible) {
        window -> draw(board.at(r).at(c).block);
      }
    }
  }
}

bool Board::updatePosition(Shape * shape, int offsetR, int offsetC) {
  // check if new position is valid
  for (int i = 0; i < 4; i++) {
    int checkR = (shape -> row.at(i)) + offsetR;
    int checkC = (shape -> col.at(i)) + offsetC;

    // out of range
    if ((checkC > BOARDC - 1) || (checkC < 0)) return false;
    if (checkR > BOARDR - 1) return false;

    // occupied
    if (board.at(checkR).at(checkC).isVisible) return false;
  }

  for (int i = 0; i < 4; i++) {
    int currentR = (shape -> row.at(i));
    int currentC = (shape -> col.at(i));

    (shape -> row.at(i)) = currentR + offsetR;
    (shape -> col.at(i)) = currentC + offsetC;
  }

  return true;
}

int Board::clearFullRows() {
  int fullRows = 0;
  for (int i = 0; i < BOARDR; i++) {
    // Count how many blocks are visible in a row
    int visibleBlocks = 0;
    for (int j = 0; j < BOARDC; j++) {
      if (board.at(i).at(j).isVisible) visibleBlocks++;
    }

    // Check if a row is full
    if (visibleBlocks == BOARDC) {
      fullRows++;

      // Move all elements above the full row down
      for (int k = i; k > 0; k--) {
        board.at(k) = board.at(k - 1);
        for (int q = 0; q < BOARDC; q++) {
          board.at(k).at(q).block.move(0, CELLSIZE);
        }
      }

      // Refill the first row as empty
      for (int g = 0; g < BOARDC; g++) {
        board.at(0).at(g) = Block(sf::Color::Transparent, false);
      }
    }
  }

  return fullRows;
}
