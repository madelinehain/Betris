#ifndef SHAPESTRUCT_HPP_
#define SHAPESTRUCT_HPP_

#include <vector>
#include "blockStruct.hpp"
#include <SFML/Graphics.hpp>

using namespace std;

extern const int CELLSIZE;

// SHAPE CLASS DEFINITION
struct Shape {
 public:
  vector<Block> shapes;
  vector<int> row, col;
  int rotations;
  int ShapeID = rand() % 6;
  // Reference board's coordinates
  vector<vector<int>> reference;
  sf::Color color;

  // Shape initializer based on color and row/col
  Shape(sf::Color Color, vector<int> r, vector<int> c);

  // Helper functions
  void draw(sf::RenderWindow *, bool);
  void rotate();
  // void alignShape();
};

#endif  // SHAPESTRUCT_HPP_
