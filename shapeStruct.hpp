#ifndef SHAPESTRUCT_HPP_
#define SHAPESTRUCT_HPP_

#include <vector>
#include "blockStruct.hpp"
#include <SFML/Graphics.hpp>

using namespace std;

extern const int CELLSIZE;

struct Shape {
 public:
  vector<Block> shapes;
  vector<int> row, col;
  int rotations;
  int ShapeID = rand() % 6;
  // Reference shape's coordinates on the board
  vector<vector<int>> reference;
  sf::Color color;

  Shape(sf::Color Color, vector<int> r, vector<int> c);
  void draw(sf::RenderWindow *, bool);
  void rotate();
  // void alignShape();
};

#endif  // SHAPESTRUCT_HPP_
