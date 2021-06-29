#include <array>
#include <vector>
#include <SFML/Graphics.hpp>

using std::array;
using std::vector;

constexpr int BOARDLENGTH_INBLOCKS = 10;
constexpr int BOARDHEIGHT_INBLOCKS = 20;

class Piece {
 public:
  vector<sf::Vector2f> blocks {4};
  sf::Vector2f origin;  // R
  sf::Color pieceColor;
  int PieceID, nextPieceID;

  Piece();
  bool canPieceMove(int board[][BOARDLENGTH_INBLOCKS], int chx, int chy);
  void rotate();
  void drop();

};
