#include "blockStruct.hpp"
#include <SFML/Graphics.hpp>
using namespace std;

// Block constructor
Block::Block(sf::Color blockColor, bool visibility) {
  block.setSize((sf::Vector2f(CELLSIZE, CELLSIZE)));
  block.setFillColor(blockColor);
  block.setOutlineThickness(-2);
  block.setOutlineColor(sf::Color::White);
  isVisible = visibility;
}
