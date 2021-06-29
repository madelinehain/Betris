// Copyright 2021 Madeline Clare Hain maddiech@bu.edu
// Copyright 2021 Mallory Gerosa gerosam@bu.edu
// https://github.com/madelinehain/EC327_Team_10_Final_Project.git
#include <chrono>
#include <ctime>
#include <iostream>
#include "Piece.hpp"
#include <SFML/Graphics.hpp>

using std::array;
using std::cout;
using std::to_string;
using std::vector;
using sf::Vector2;

extern const float CELLSIZE;

int main() {
  int points;
  int board[BOARDLENGTH_INBLOCKS][BOARDHEIGHT_INBLOCKS] {0};
  bool isGameOver = false, canMove = true, piecePlaced = false;
  sf::RenderWindow window(sf::VideoMode(720, 800), "Tetris");
  window.setFramerateLimit(20);
  sf::RectangleShape cell(sf::Vector2f(CELLSIZE, CELLSIZE));  // 4 cells per block
  Piece currentPiece;

  sf::Font font;
  sf::Texture t, titleLoad, nextLoad, scoreLoad;
  t.loadFromFile("Resources/background.png");
  titleLoad.loadFromFile("Resources/titleSmall.png");
  nextLoad.loadFromFile("Resources/next.png");
  scoreLoad.loadFromFile("Resources/score.png");
  font.loadFromFile("Resources/TetrisFont.ttf");
  if (!t.loadFromFile("Resources/background.png")) return -1;
  if (!titleLoad.loadFromFile("Resources/titleSmall.png")) return -1;
  if (!nextLoad.loadFromFile("Resources/next.png")) return -1;
  if (!scoreLoad.loadFromFile("Resources/score.png")) return -1;
  if (!font.loadFromFile("Resources/TetrisFont.ttf")) return -1;

  sf::Sprite background(t), title(titleLoad), next(nextLoad), score(scoreLoad);

  background.setPosition(0, 0);
  title.setPosition(420, 20);
  next.setPosition(440, 220);
  score.setPosition(420, 460);

  sf::Text gameScore;
  sf::FloatRect scorebox = gameScore.getGlobalBounds();
  gameScore.setString(to_string(points));
  gameScore.setCharacterSize(40);
  gameScore.setFillColor(sf::Color::White);
  gameScore.setOrigin(scorebox.width / 2.0, 0);
  gameScore.setPosition(560, 460);


  while (window.isOpen()) {
    sf::Event event;
    while (true) {
      // check if game is over by checking top row
      for (int i = 0; i < BOARDLENGTH_INBLOCKS; i++) {
        if (board[i][BOARDHEIGHT_INBLOCKS] == 1) isGameOver = true;
      }
      // reset board
      if (isGameOver == true) {
        points = 0;
        board[BOARDLENGTH_INBLOCKS][BOARDHEIGHT_INBLOCKS] = {0};
        isGameOver = false;
        // maybe we do something about starting a new game here
      }
      // create a new piece
      if (piecePlaced == false) {
        Piece nextPiece();
         Piece currentPiece;
        piecePlaced = false;
      }
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
            if (currentPiece.canPieceMove(board, -1, 0) == true) {
              for (int block = 0; block < 4; block++) {
                currentPiece.blocks.at(block).x -= 1;
              }
            }
          }
          // move piece right
          if (event.key.code == sf::Keyboard::Right) {
            if (currentPiece.canPieceMove(board, 0, 1) == true) {
              for (int block = 0; block < 4; block++) {
                currentPiece.blocks.at(block).x += 1;
              }
            }
          }
          if (event.key.code == sf::Keyboard::Down) {
            currentPiece.drop(board);
            piecePlaced = true;
          }
        }
      }

      window.clear();

      window.draw(background);
      window.draw(title);
      window.draw(next);
      window.draw(score);

      window.display();
    }
  }
  return 0;
}
