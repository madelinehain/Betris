#include "blockStruct.hpp"
#include "shapeStruct.hpp"
#include<SFML/Graphics.hpp>
using namespace std;


  // Block constructor
  Block::Block(sf::Color color, bool visibility) {
    blockColor = color;
    isVisible = visibility;
    block.setSize((sf::Vector2f(CELLSIZE, CELLSIZE)));
    block.setFillColor(color);
    block.setOutlineThickness(-2);
    block.setOutlineColor(sf::Color::White);
  }