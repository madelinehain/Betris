#ifndef BLOCKSTRUCT_HPP_
#define BLOCKSTRUCT_HPP_

#include <SFML/Graphics.hpp>
using namespace std;

const int CELLSIZE = 40;
const int BOARDR = 20;
const int BOARDC = 10;

struct Block {
 public:
  sf::RectangleShape block;
  sf::Color blockColor;
  bool isVisible;

  Block(sf::Color color, bool visibility);
};

#endif  // BLOCKSTRUCT_HPP_
