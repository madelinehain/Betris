#ifndef SHAPE_STRUCT
#define SHAPE_STRUCT
#include <vector>
#include <SFML/Graphics.hpp>
#include "blockStruct.hpp"

using namespace std;

extern const float CELLSIZE;

struct Shape {
public:
  vector<Block> shapes {4};
  vector<int> row, col;
    vector<vector<int>> reference (4, vector<int>(4, 0));

  sf::Color shapeColor;
  int shapeID;

  // Constructor
  Shape(int ID);
  // Helper functions
  void draw(sf::RenderWindow * window);
  void drawNext(sf::RenderWindow * window);
  void rotate();
  void alignShape();
};
#endif  // SHAPE_STRUCT