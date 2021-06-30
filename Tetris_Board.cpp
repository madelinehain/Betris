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

double besttime() {
  auto now = std::chrono::high_resolution_clock::now();
  auto dur = now.time_since_epoch();
  return dur.count() / 1'000'000'000.0;
}

int main() {
  int points;
  int board[BOARDLENGTH_INBLOCKS][BOARDHEIGHT_INBLOCKS] {0};
  bool isGameOver = false, canMove = true, piecePlaced = false;

  sf::RenderWindow window(sf::VideoMode(720, 800), "Tetris");
  window.setFramerateLimit(20);
  Piece currentPiece;
  Piece nextPiece = currentPiece.createNewPiece();

  // 4 cells per block
  sf::RectangleShape cell(sf::Vector2f(CELLSIZE, CELLSIZE));
  sf::RectangleShape nextcell(sf::Vector2f(CELLSIZE, CELLSIZE));

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
  gameScore.setFont(font);
  gameScore.setCharacterSize(45);
  gameScore.setFillColor(sf::Color::Red);
  gameScore.setOrigin(scorebox.width / 2.0, 0);
  gameScore.setOutlineColor(sf::Color::White);
  gameScore.setOutlineThickness(2);
  gameScore.setPosition(440, 525);

  sf::Text gameTime;
  gameTime.setFont(font);
  gameTime.setCharacterSize(45);
  gameTime.setFillColor(sf::Color::Blue);
  gameTime.setOrigin(scorebox.width / 2.0, 0);
  gameTime.setOutlineColor(sf::Color::White);
  gameTime.setOutlineThickness(2);
  gameTime.setPosition(440, 720);

  sf::Text gameLevel;
  gameLevel.setFont(font);
  gameLevel.setCharacterSize(45);
  gameLevel.setFillColor(sf::Color::Yellow);
  gameLevel.setOutlineColor(sf::Color::White);
  gameLevel.setOutlineThickness(2);
  gameLevel.setPosition(440, 620);

  sf::RectangleShape testsquare(sf::Vector2f(CELLSIZE, CELLSIZE));
  testsquare.setFillColor(sf::Color::Red);
  testsquare.setPosition(160, 0);


  while (window.isOpen()) {

  //initialize the time
  std::time_t initialtime = std::time(NULL);
    std::tm now = *std::localtime(&initialtime);
    double speed = 1.0;
    int level = 0;

    sf::Event event;

    while (true) {


      //Display score and time
      std::time_t time = std::time(NULL);
      std::tm now = *std::localtime(&time);
      double accurate_time = besttime();
      double differ = accurate_time - time;
      int dispscore;
      int nowtime = time - initialtime;

      //change speed
      if ((differ < 0.25) && (differ > 0.20))
        testsquare.move(0, 40 * (1 + level));
      if (nowtime > 10)  dispscore = level * nowtime;
      else dispscore = nowtime;

      gameScore.setString(to_string(dispscore));

      level = nowtime / 10;

      gameLevel.setString(to_string(level));
      gameTime.setString(to_string(nowtime));


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
      if (piecePlaced == true) {
        currentPiece = nextPiece;
        nextPiece = currentPiece.createNewPiece();
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
            if (currentPiece.canPieceMove(board, 1, 0) == true) {
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
      gameScore.setString(to_string(points));

      window.draw(background);
      window.draw(title);
      window.draw(next);
      window.draw(score);
      window.draw(gameScore);
      window.draw(gameLevel);
      window.draw(gameTime);
      window.draw(testsquare);
      currentPiece.drawPiece(cell, &window);
      nextPiece.drawPiece(nextcell, &window);

      window.display();
    }
  }
  return 0;
}
