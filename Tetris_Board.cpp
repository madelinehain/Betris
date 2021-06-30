// Copyright 2021 Madeline Clare Hain maddiech@bu.edu
// Copyright 2021 Mallory Gerosa gerosam@bu.edu
// https://github.com/madelinehain/EC327_Team_10_Final_Project.git

#include <chrono>
#include <ctime>
#include <iostream>
#include "Piece.hpp"
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

using std::array;
using std::cout;
using std::to_string;
using std::vector;
using sf::Vector2;

extern const float CELLSIZE;

// calculate accurate time
double besttime() {
  auto now = std::chrono::high_resolution_clock::now();
  auto dur = now.time_since_epoch();
  return dur.count() / 1'000'000'000.0;
}

int main() {
  int points, nowtime, level;
  double accurate_time, differ, speed;
  int board[BOARDLENGTH_INBLOCKS][BOARDHEIGHT_INBLOCKS] {0};
  bool isGameOver = false, canMove = true, piecePlaced = false;

  sf::RenderWindow window(sf::VideoMode(720, 800), "Tetris");
  window.setFramerateLimit(10);

  Piece currentPiece;
  Piece nextPiece = currentPiece.createNewPiece();
  // blocks of current and next pieces
  sf::RectangleShape cell(sf::Vector2f(CELLSIZE, CELLSIZE));
  sf::RectangleShape nextCell(sf::Vector2f(CELLSIZE, CELLSIZE));

  sf::Music bgmusic;
  sf::Font font;
  sf::Texture t, titleLoad, nextLoad, scoreLoad;
  // load files for textures, music, and fonts
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

  sf::Sprite background(t), titlebox(titleLoad), nextbox(nextLoad), scorebox(scoreLoad);
  background.setPosition(0, 0);
  titlebox.setPosition(420, 20);
  nextbox.setPosition(440, 220);
  scorebox.setPosition(420, 460);

  sf::Text gameScore;
  sf::FloatRect gameScoreBox = gameScore.getGlobalBounds();
  gameScore.setFont(font);
  gameScore.setCharacterSize(45);
  gameScore.setFillColor(sf::Color::Red);
  gameScore.setOrigin(gameScoreBox.width / 2.0, 0);
  gameScore.setOutlineColor(sf::Color::White);
  gameScore.setOutlineThickness(2);
  gameScore.setPosition(440, 525);

  sf::Text gameTime;
  gameTime.setFont(font);
  gameTime.setCharacterSize(45);
  gameTime.setFillColor(sf::Color::Blue);
  gameTime.setOrigin(gameScoreBox.width / 2.0, 0);
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
    // initialize the time
    std::time_t initialtime = std::time(NULL);
    std::tm now = *std::localtime(&initialtime);
    speed = 1.0;
    level = 0;

    sf::Event event;
    while (true) {
      // calculate time
      std::time_t time = std::time(NULL);
      std::tm now = *std::localtime(&time);
      accurate_time = besttime();
      differ = accurate_time - time;
      nowtime = time - initialtime;

      // calculate score
      if ((differ < 0.25) && (differ > 0.20))
        testsquare.move(0, 40 * (1 + level));
      if (nowtime > 10)  points = level * nowtime;
      else 
        points = nowtime;

      level = nowtime / 10;
      // update constantly
      gameScore.setString(to_string(points));
      gameLevel.setString(to_string(level));
      gameTime.setString(to_string(nowtime));

      // check if game is over by checking top row or if a piece has been placed
      for (int i = 0; i < BOARDLENGTH_INBLOCKS; i++) {
        if (board[i][BOARDHEIGHT_INBLOCKS] == 1) isGameOver = true;
        if (currentPiece.canPieceMove(board, 0, 1) == false) piecePlaced = true;
      }
      // reset game
      if (isGameOver == true) {
        points = 0;
        board[BOARDLENGTH_INBLOCKS][BOARDHEIGHT_INBLOCKS] = {0};
        isGameOver = false;
        // maybe we do something about starting a new game here
      }
      // current piece is now the next piece
      if (piecePlaced == true) {
        currentPiece = nextPiece;
        nextPiece = currentPiece.createNewPiece();
        piecePlaced = false;
        for (int block = 0; block < 4; block++)
          currentPiece.blocks.at(block).x += 4;
      }
      // not exactly sure what this does
      for (int block = 0; block < 4; block++) {
        if ((differ < 0.25) && (differ > 0.15))
          currentPiece.blocks.at(block).y += (1 + level);
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
            // check piece and board bounds collision
            if (currentPiece.canPieceMove(board, -1, 0) == true) {
              for (int block = 0; block < 4; block++) {
                currentPiece.blocks.at(block).x -= 1;
              }
            }
          }
          // move piece right
          if (event.key.code == sf::Keyboard::Right) {
            // check piece and board bounds collision
            if (currentPiece.canPieceMove(board, 1, 0) == true) {
              for (int block = 0; block < 4; block++) {
                currentPiece.blocks.at(block).x += 1;
              }
            }
          }
          // drop piece to the last possible row
          if (event.key.code == sf::Keyboard::Down) {
            currentPiece.drop(board);
            piecePlaced = true;
          }
        }
      }
      window.clear();

      window.draw(background);
      window.draw(titlebox);
      window.draw(nextbox);
      window.draw(scorebox);
      window.draw(gameScore);
      window.draw(gameLevel);
      window.draw(gameTime);
      window.draw(testsquare);
      currentPiece.drawPiece(cell, &window);
      nextPiece.drawNextPiece(nextCell, &window);

      window.display();
    }
  }
  return 0;
}
