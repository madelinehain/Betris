#ifndef BLOCK_STRUCT
#define BLOCK_STRUCT
#include<SFML/Graphics.hpp>
using namespace std;

const float CELLSIZE = 40;

// BLOCK STRUCT DEFINITION
struct Block {
public:
  sf::RectangleShape block;
  sf::Color blockColor;
 bool isVisible;

  // Block constructor
  Block(sf::Color color, bool visibility);
};
#endif // BLOCK_STRUCT