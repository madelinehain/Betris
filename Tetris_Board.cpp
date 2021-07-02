// Copyright 2021 Madeline Clare Hain   maddiech@bu.edu
//                Ava Remler            aremler@bu.edu
//                Mallory Gerosa        gerosam@bu.edu
//                Abdulaziz AlMailam    almailam@bu.edu

#include <SFML/Graphics.hpp>
#include "boardStruct.hpp"
#include "math.h"

#include <algorithm>
#include <vector>
#include <iostream>
#include <string>

using namespace std;

#define PI 3.14159265359

extern const int BOARDC;
extern const int BOARDR;
extern const int CELLSIZE;
extern const int gameSpeed = 2;



// MAIN FUNCTION HEADERS
void checkEvents(sf::RenderWindow *, sf::Event, Shape *, Board *, sf::Sprite);
bool checkEventsMenu(sf::RenderWindow * window, sf::Event event);
Shape getCombination(int);




int main() {
  // Window settings
  sf::RenderWindow window(sf::VideoMode(720, 800), "Betris");
  window.setFramerateLimit(3);

  // Load miscellaneous items
  srand(time(NULL));

  sf::Font font;
  font.loadFromFile("Resources/TetrisFont.ttf");

  sf::Texture b, g, s, p;

  b.loadFromFile("Resources/Board.png");
  sf::Sprite background(b);

  g.loadFromFile("Resources/GameOver.png");
  sf::Sprite endScreen(g);

  s.loadFromFile("Resources/Start.png");
  sf::Sprite startScreen(s);

  p.loadFromFile("Resources/Pause.png");
  sf::Sprite pause(p);


  // Active/live window
  while (window.isOpen()) {
    bool advance = false;

    window.clear();
    window.draw(startScreen);
    window.display();

    // Wait until player starts the game
    do {
      sf::Event event;
      advance = checkEventsMenu(&window, event);
    } while (!advance);

    window.clear();

    // Setup game
    Board board;
    bool activeShape = true;
    bool gameOver = false;

    // Keep track of game time
    sf::Clock gameClock;

    // Create time, score, and level objects
    sf::Text time("999", font, 50);
    time.setPosition(450, 715);

    sf::Text Score("999", font, 50);
    Score.setPosition(450, 520);
    int score = 4;

    sf::Text Level("999", font, 50);
    Level.setPosition(450, 615);
    int level = 1;

    sf::Time refreshTime;
    sf::Clock refreshClock;

    // Create two new pieces
    Shape currentShape = getCombination(rand() % 6);
    Shape nextShape = getCombination(rand() % 6);


    // Check if game is still active
    while (!gameOver) {
      // Create a new piece if there are no active shapes in motion
      if (!activeShape) {
        currentShape = nextShape;
        nextShape = getCombination(rand() % 6);
        score += 2;
        activeShape = true;
      }

      // Update the time
      int timeNum = gameClock.getElapsedTime().asSeconds();
      time.setString(to_string(timeNum));

      // Get the current Level
      level = timeNum / BOARDR + 1;
      Level.setString(to_string(level));

      // Get the current Score
      int scoredisp = score * (1 + level);
      Score.setString(to_string(scoredisp));

      refreshTime += refreshClock.restart();

      // Update piece position
      if (refreshTime.asSeconds() >= gameSpeed) {
        if (!board.updatePosition(&currentShape, 1, 0)) {
          // Copy blocks
          for (int i = 0; i < 4; i++) {
            int row = currentShape.row.at(i);
            int col = currentShape.col.at(i);

            board.board.at(row).at(col) = currentShape.shapes.at(i);
          }
          activeShape = false;
        }
      }

      // Checks all window events
      sf::Event event;
      checkEvents(&window, event, &currentShape, &board, pause);


      // Draw all elements & display the window
      board.clearFullRows();
      window.clear();

      window.draw(background);
      window.draw(time);
      currentShape.draw(&window, false);
      board.draw(&window);
      nextShape.draw(&window, true);
      window.draw(Score);
      window.draw(Level);
      window.display();

      // Update game status
      gameOver = board.isGameOver();
    }

    // Game over
    advance = false;

    window.clear();
    window.draw(endScreen);
    window.display();

    // Wait until player returns to the main menu or quits
    do {
      sf::Event event;
      advance = checkEventsMenu(&window, event);
    } while (!advance);
  }
}




// MAIN FUNCTIONS -------------------------



// Checks all game events
void checkEvents(sf::RenderWindow * window, sf::Event event,
                Shape * s, Board * b, sf::Sprite pause) {
  while (window -> pollEvent(event)) {
    // Close window
    if (event.type == sf::Event::Closed) exit(1);

    // Keyboard events
    if (event.type == sf::Event::KeyPressed) {
      sf::Keyboard::Key key = event.key.code;
      if (key == sf::Keyboard::Up) s -> rotate();
      if (key == sf::Keyboard::Escape) exit(1);
      if (key == sf::Keyboard::Right) b -> updatePosition(s, 0, 1);
      if (key == sf::Keyboard::Left) b -> updatePosition(s, 0, -1);
      if (key == sf::Keyboard::P || key == sf::Keyboard::Space) {
        bool endPause = false;

        window -> clear();
        window -> draw(pause);
        window -> display();

        do {
          window -> pollEvent(event);
          if (event.type == sf::Event::KeyPressed) {
            if (event.key.code == sf::Keyboard::Enter) endPause = true;
            if (event.key.code == sf::Keyboard::Escape) exit(1);
          }
        } while (!endPause);
      }
    }
  }
}


bool checkEventsMenu(sf::RenderWindow * window, sf::Event event) {
  while (window -> pollEvent(event)) {
    // Close window
    if (event.type == sf::Event::Closed) exit(1);

    // Keyboard events
    if (event.type == sf::Event::KeyPressed) {
      if (event.key.code == sf::Keyboard::Escape) exit(1);
      if (event.key.code == sf::Keyboard::Enter) return true;
    }
  }
  return false;
}


Shape getCombination(int ShapeID) {
  vector<int> row, col;
  sf::Color shapeColor;

  if (ShapeID == 0) {  // I
    row = {0, 0, 0, 0};
    col = {0, 1, 2, 3};
    shapeColor = sf::Color(50, 250, 0);  // green

  } else if (ShapeID == 1) {  // Z
    row = {0, 0, 1, 1};
    col = {0, 1, 1, 2};
    shapeColor = sf::Color(230, 0, 0);  // red

  } else if (ShapeID == 2) {  // S (reverse Z)
    row = {1, 0, 1, 0};
    col = {0, 1, 1, 2};
    shapeColor = sf::Color(215, 50, 235);  // magenta

  } else if (ShapeID == 3) {  // L
    row = {0, 0, 0, 1};
    col = {0, 1, 2, 2};
    shapeColor = sf::Color(255, 235, 20);  // yellow

  } else if (ShapeID == 4) {  // J (reverse L)
    row = {1, 1, 0, 1};
    col = {0, 1, 2, 2};
    shapeColor = sf::Color(23, 35, 200);  // blue

  } else if (ShapeID == 5) {  // O (square)
    row = {0, 0, 1, 1};
    col = {0, 1, 0, 1};
    shapeColor = sf::Color(255, 135, 0);  // orange

  } else {
    row = {0, 0, 1, 0};  // T
    col = {0, 1, 1, 2};
    shapeColor = sf::Color(5, 245, 245);  // cyan
  }

  return Shape(shapeColor, row, col);
}
