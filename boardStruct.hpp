#ifndef BOARDSTRUCT_HPP_
#define BOARDSTRUCT_HPP_

#include <vector>
#include "shapeStruct.hpp"
#include "blockStruct.hpp"
using std::vector;

struct Board {
 public:
  vector<vector<Block>> board;
  vector<int> r, c;
  int boardWeight;

  // Initialize board with invisible blocks
  Board();
  // Helper functions
  void draw(sf::RenderWindow *);
  bool updatePosition(Shape *, int, int);
  int clearFullRows();
  bool isGameOver();
};
#endif  // BOARDSTRUCT_HPP_
