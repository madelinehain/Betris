#include <array>
#include <vector>
#include <SFML/Graphics.hpp>

using std::array;
using std::vector;
using sf::Vector2;

const int BOARDLENGTH = 400;
const int BOARDLENGTH_INBLOCKS = 10;
const int BOARDHEIGHT = 800;
const int BOARDHEIGHT_INBLOCKS = 20;
const int WINDOWHEIGHT = 1000;
const float CELLSIZE = 40;

class Piece {
 public:
  vector<sf::Vector2f> blocks {4};
  sf::Vector2f origin;  // R
  sf::Color pieceColor;
  int PieceID, nextPieceID;

  explicit Piece() {
    PieceID = nextPieceID;
    nextPieceID = rand() % 7;
    // I (straight)
    if (PieceID == 0) {
      blocks.at(0).x = 0;  // x o o o
      blocks.at(0).y = 0;  // R o o o
      blocks.at(1).x = 0;  // x o o o
      blocks.at(1).y = 1;  // x o o o
      blocks.at(2).x = 0;
      blocks.at(2).y = 2;
      blocks.at(3).x = 0;
      blocks.at(3).x = 3;
      origin.x = 1;
      origin.y = 0;
      pieceColor = sf::Color::Green;
    }
    // Z
    if (PieceID == 1) {
      blocks.at(0).x = 0;   // x o o o
      blocks.at(0).y = 0;   // R x o o
      blocks.at(1).x = 0;   // o x o o
      blocks.at(1).y = 1;   // o o o o
      blocks.at(2).x = 1;
      blocks.at(2).y = 1;
      blocks.at(3).x = 1;
      blocks.at(3).y = 2;
      origin.x = 0;
      origin.y = 1;
      pieceColor = sf::Color::Red;
    }
    // S (reverse Z)
    if (PieceID == 2) {
      blocks.at(0).x = 1;   // o x o o
      blocks.at(0).y = 0;   // R x o o
      blocks.at(1).x = 0;   // x o o o
      blocks.at(1).y = 1;   // o o o o
      blocks.at(2).x = 1;
      blocks.at(2).y = 1;
      blocks.at(3).x = 0;
      blocks.at(3).y = 2;
      origin.x = 1;
      origin.y = 0;
      pieceColor = sf::Color::Blue;
    }
    // L
    if (PieceID == 3) {
      blocks.at(0).x = 0;   // x o o o
      blocks.at(0).y = 0;   // R o o o
      blocks.at(1).x = 0;   // x x o o
      blocks.at(1).y = 1;   // o o o o
      blocks.at(2).x = 0;
      blocks.at(2).y = 2;
      blocks.at(3).x = 1;
      blocks.at(3).y = 2;
      origin.x = 1;
      origin.y = 0;
      pieceColor = sf::Color::Yellow;
    }
    // J (reverse L)
    if (PieceID == 4) {
      blocks.at(0).x = 1;   // o x o o
      blocks.at(0).y = 0;   // o R o o
      blocks.at(1).x = 1;   // x x o o
      blocks.at(1).y = 1;   // o o o o
      blocks.at(2).x = 0;
      blocks.at(2).y = 2;
      blocks.at(2).x = 1;
      blocks.at(3).y = 2;
      origin.x = 1;
      origin.y = 1;
      pieceColor = sf::Color::Magenta;
    }
    // O (square)
    if (PieceID == 5) {
      blocks.at(0).x = 0;   // x x o o
      blocks.at(0).y = 0;   // x x o o
      blocks.at(1).x = 0;   // o o o o
      blocks.at(1).y = 1;   // o o o o
      blocks.at(2).x = 1;
      blocks.at(2).y - 0;
      blocks.at(3).x = 1;
      blocks.at(3).y = 1;
      pieceColor = sf::Color(120, 20, 170, 100);
    }
    // T
    if (PieceID == 6) {
      blocks.at(0).x = 0;
      blocks.at(0).y = 0;   // x o o o
      blocks.at(1).x = 0;   // R x o o
      blocks.at(1).y = 1;   // x o o o
      blocks.at(2).x = 1;   // o o o o
      blocks.at(2).y = 1;
      blocks.at(3).x = 0;
      blocks.at(3).y = 2;
      origin.x = 1;
      origin.y = 0;
      pieceColor = sf::Color::Cyan;
    }
  }

  bool canPieceMove(int board[][BOARDLENGTH_INBLOCKS], int chx, int chy) {
    bool canMove = true;
    for (int i = 0; i < 4; i++) {
      // check left and right
      if ((blocks.at(i).x + chx < 0) || (board[(int)blocks.at(i).x + chx][(int)blocks.at(i).y] == 1)
        || (blocks.at(i).x + chx > BOARDLENGTH_INBLOCKS))
        canMove = false;
      // check down
      if ((blocks.at(i).y + chy < 0) || (board[(int)blocks.at(i).x][(int)blocks.at(i).y + chy] == 1)
        || (blocks.at(i).y + chy > BOARDHEIGHT_INBLOCKS))
        canMove = false;
    }
    return canMove;
  }

  void rotate() {
    if (PieceID == 5) return;
  }

  void drop() {

  }
};

// initial piece position x+boardwidth/2 * CELLSIZE, y * CELLSIZE

// void drawPiece(Piece p, sf::RectangleShape cell, sf::RenderWindow window) {
//   cell.setFillColor(p.pieceColor);
//   // cell.setTexture
//   // cell.setOutlineColor(sf::Color::Black);
//   // cell.setOutlineThickness(-2);

//   for (int i = 0; i < 4; i++) {
//     cell.setPosition(BOARDLENGTH_INBLOCKS /2 + p.blocks.at(i).x + newx * CELLSIZE,
//     p.blocks.at(i).y + newy * CELLSIZE);
//     window.draw(cell);
//   }
// }


int main() {
  int score;
  int board[BOARDHEIGHT_INBLOCKS][BOARDLENGTH_INBLOCKS];
  bool rotate = false;
  bool isGameOver = false;
  bool canMove = true;
  sf::RectangleShape cell(sf::Vector2f(CELLSIZE, CELLSIZE));
  sf::RenderWindow window(sf::VideoMode(BOARDLENGTH, WINDOWHEIGHT),
                          "Tetrominoes");
  Piece p = Piece();
  // title
  sf::Text gameName;
  gameName.setString("Tetrominoes");
  sf::Font gameNamefont;
  // font.loadFromFile
  // gameName.setFont(gameNamefont);
  // gameName.setCharacterSize(40);
  // gameName.setFillColor();
  // gameName.setPosition();

  sf::Font font;

  // score
  sf::Text scoreWord;
  scoreWord.setString("Score");
  // scoreWord.setFont(font);
  // scoreWord.setCharacerSize();
  // scoreWord.setFillColor();
  // scoreWord.setPosition();

  // score points
  // sf::Text points();
  // points.setFonr(font);
  // points.setCharacterSize();
  // points.setFillColor();
  // points.setPosition();


  // start game
  while (window.isOpen()) {
    while (true) {
      // check for game over
      for (int i = 0; i < BOARDLENGTH_INBLOCKS; i++) {
        if (board[i][BOARDHEIGHT_INBLOCKS] == 1) isGameOver = true;
      }
      // reset board
      if (isGameOver == true) {
        score = 0;
        board[BOARDHEIGHT_INBLOCKS][BOARDLENGTH_INBLOCKS] = {0};
        isGameOver = false;
      }
      sf::Event event;
      while (window.pollEvent(event)) {
        // close window
        if (event.type == sf::Event::Closed) {
          window.close();
          return 0;
        }
        // if a key is pressed
        if (event.type == sf::Event::KeyPressed) {
          // rotate piece
          if (event.key.code == sf::Keyboard::Up) {
            // to do: rotate()
          }
          // move piece left
          if (event.key.code == sf::Keyboard::Left) {
            // check that coordinates are within the bounds of the board
            // and that the space is available
            if (p.canPieceMove(board, 0, -1) == true) {
              for (int i = 0; i < 4; i++) {
                p.blocks.at(i).x -= 1;
              }      
            }
          }
          // move piece right
          if (event.key.code == sf::Keyboard::Right) {
            if (p.canPieceMove(board, 0, 1) == true) {
              for (int i = 0; i < 4; i++) {
                p.blocks.at(i).x += 1;
              }              
            }
          }
          if (event.key.code == sf::Keyboard::Down) {
            // to do: drop()
          }
        }
      }
      window.clear();

      // window.display(gameName);
      // window.display(score);
      // window.display(points);
      window.display();
    }
  }
}
