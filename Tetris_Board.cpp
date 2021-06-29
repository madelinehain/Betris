// Copyright 2021 Madeline Clare Hain maddiech@bu.edu
// Copyright 2021 Mallory Gerosa gerosam@bu.edu
// https://github.com/madelinehain/EC327_Team_10_Final_Project.git
#include <chrono>
#include <ctime>
#include <iostream>
#include "Piece.hpp"
#include <SFML/Graphics.hpp>

using std::cout;
using sf::Vector2;
using std::vector;
using std::array;

const int BOARDLENGTH = 400;
const int BOARDHEIGHT = 800;
const int WINDOWHEIGHT = 1000;
const float CELLSIZE = 40;

void createNewPiece() {
  Piece p(), newp();
}

int main() {
  int points;
  int board[BOARDHEIGHT_INBLOCKS][BOARDLENGTH_INBLOCKS];
  bool rotate = false, isGameOver = false, canMove = true;
  sf::RenderWindow window(sf::VideoMode(720, 800), "Tetris");
  sf::Texture t, titleLoad, nextLoad, scoreLoad;
  // cell representing each of the four blocks of a peice
  sf::RectangleShape cell(sf::Vector2f(CELLSIZE, CELLSIZE));
  Piece currentPiece, nextPiece;

  t.loadFromFile("Images/background.png");
  titleLoad.loadFromFile("Images/titleSmall.png");
  nextLoad.loadFromFile("Images/next.png");
  scoreLoad.loadFromFile("Images/score.png");

  if (!t.loadFromFile("Images/background.png")) return -1;
  if (!titleLoad.loadFromFile("Images/titleSmall.png")) return -1;
  if (!nextLoad.loadFromFile("Images/next.png")) return -1;
  if (!scoreLoad.loadFromFile("Images/score.png")) return -1;

  sf::Sprite background(t);
  sf::Sprite title(titleLoad);
  sf::Sprite next(nextLoad);
  sf::Sprite score(scoreLoad);

  window.setFramerateLimit(20);

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
        board[BOARDHEIGHT_INBLOCKS][BOARDLENGTH_INBLOCKS] = {0};
        isGameOver = false;
        // maybe we do something about starting a new game here
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
            if (currentPiece.canPieceMove(board, 0, -1) == true) {
              for (int i = 0; i < 4; i++) {
                currentPiece.blocks.at(i).x -= 1;
              }
            }
          }
          // move piece right
          if (event.key.code == sf::Keyboard::Right) {
            if (currentPiece.canPieceMove(board, 0, 1) == true) {
              for (int i = 0; i < 4; i++) {
                currentPiece.blocks.at(i).x += 1;
              }
            }
          }
          if (event.key.code == sf::Keyboard::Down) {
            // to do: drop()
          }
        }
      }

      window.clear();
      background.setPosition(0, 0);
      title.setPosition(420, 20);
      next.setPosition(440, 220);
      score.setPosition(420, 460);
      window.draw(background);
      window.draw(title);
      window.draw(next);
      window.draw(score);
      window.display();
    }
  }
  return 0;
}
