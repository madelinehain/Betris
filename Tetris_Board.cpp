// Copyright 2021 Madeline Clare Hain   maddiech@bu.edu
//                Ava Remler            aremler@bu.edu
//                Mallory Gerosa        gerosam@bu.edu
//                Abdulaziz AlMailam    almailam@bu.edu

#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include <iostream>
#include "math.h"
#include <algorithm>

using namespace std;

#define PI 3.14159265359

const int boardC = 10;
const int boardR = 20;
const int shapeXY = 40;
const int gameSpeed = 2;


// BLOCK CLASS DEFINITION
struct Block {
  sf::RectangleShape block;
  bool isVisible;

  // Block constructor
  Block(sf::Color color, bool visibility) {
    block.setSize((sf::Vector2f(shapeXY, shapeXY)));
    block.setFillColor(color);
    block.setOutlineThickness(-2);
    block.setOutlineColor(sf::Color::White);
    isVisible = visibility;
  }
};





// SHAPE CLASS DEFINITION
struct Shape {
  vector<Block> shapes;
  vector<int> row, col;
  int rotations, ShapeID;

  // reference shape's coordinates
  vector<vector<int>> reference;

  sf::Color color;

  // Shape initializer based on color and row/col
  Shape(sf::Color Color, vector<int> r, vector<int> c) {
    color = Color;
    row = r;
    col = c;
    rotations = 0;
    ShapeID = rand() % 6;

    vector<vector<int>> reference (4, vector<int>(4, 0));

    for (int i = 0; i < 4; i++) {
      Block newBlock(Color, true);
      shapes.push_back(newBlock);
      reference.at(r.at(i)).at(c.at(i)) = i + 1;
    }
  };


  // helper functions
  void draw(sf::RenderWindow *, bool);
  // void alignShape();
};












// BOARD CLASS DEFINITION
struct Board {
  vector<vector<Block>> board;
  int boardWeight;
  vector<int> r{(boardR, 0)};
  vector<int> c{(boardC, 0)};

  // Board initializer with invisible blocks
  Board() {
    vector<vector<Block>> content(boardR, vector<Block>(boardC, Block(sf::Color::Transparent, false)));
    board = content;
    boardWeight = 0;
  }

  // helper functions
  void draw(sf::RenderWindow *);
  bool updatePosition(Shape *, int, int);
  int clearFullRows();
  bool isGameOver();
};








// MAIN FUNCTION HEADERS
void checkEvents(sf::RenderWindow *, sf::Event, Shape *, Board *, sf::Sprite);
bool checkEventsMenu(sf::RenderWindow * window, sf::Event event);
Shape getCombination(int);
void rotate(Shape *s, Board * b);




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
      level = timeNum / boardR + 1;
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

          // Clear full rows & add to the score
          //score += board.clearFullRows();
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






// BOARD CLASS FUNCTIONS -------------------------

void Board::draw(sf::RenderWindow * window) {
  for (int r = 0; r < boardR; r++) {
    for (int c = 0; c < boardC; c++) {
      if (board.at(r).at(c).isVisible) {
        window -> draw(board.at(r).at(c).block);
      }
    }
  }
}


bool Board::updatePosition(Shape * shape, int offsetR, int offsetC) {
  // check if new position is valid
  for (int i = 0; i < 4; i++) {
    int checkR = (shape -> row.at(i)) + offsetR;
    int checkC = (shape -> col.at(i)) + offsetC;

    // out of range
    if ((checkC > 9) || (checkC < 0)) return false;
    if (checkR > 19) return false;

    // occupied
    if (board.at(checkR).at(checkC).isVisible) return false;
  }

  for (int i = 0; i < 4; i++) {
    int currentR = (shape -> row.at(i));
    int currentC = (shape -> col.at(i));

    (shape -> row.at(i)) = currentR + offsetR;
    (shape -> col.at(i)) = currentC + offsetC;
  }

  return true;
}


int Board::clearFullRows() {
  int fullRows = 0;
  for (int i = 0; i < boardR; i++) {
    // Count how many blocks are visible in a row
    int visibleBlocks = 0;
    for (int j = 0; j < boardC; j++) {
      if (board.at(i).at(j).isVisible) visibleBlocks++;
    }

    // Check if a row is full
    if (visibleBlocks == boardC) {
      fullRows++;

      // Move all elements above the full row down
      for (int k = i; k > 0; k--) {
        board.at(k) = board.at(k - 1);
        for (int q = 0; q < boardC; q++) {
          board.at(k).at(q).block.move(0, shapeXY);
        }
      }

      // Reset the first row as empty
      for (int g = 0; g < boardC; g++) {
        board.at(0).at(g) = Block(sf::Color::Transparent, false);
      }
    }
  }

  return fullRows;
}

bool Board::isGameOver() {
  for (int i = 0; i < boardC; i++) {
    if (board.at(0).at(i).isVisible) return true;
  }
  return false;
}









// SHAPE CLASS FUNCTIONS -------------------------



// Pivot is (0,1) unless ShapeID = 4 (J) then it is (1,1)
// row.at(1) and col.at(1) = pivot point (0, 1)
// a_off_x -> a offset x



//  Matrix rotation
// [cos deg  -sin deg]   [ cos deg  -sin deg]
// [sin deg   cos deg]   [-sin deg   cos deg]
//      clockwise         counter clockwise
//        [0, -1]              [0, -1]
//        [1,  0]              [-1, 0]
//         1 r                  2/3 r
// void Shape::rotate() {
//   vector<int> ycopy = row;
//   vector<int> xcopy = col;
//   int oldx, oldy, tempx, tempy, newx, newy;
//   int originx = 0;  // center of rotation for I
//   int originy = 1;

//   // O (square) no rotation
//   if (ShapeID == 5) return;

//   // I (line)
//   if (ShapeID == 0) {
//     rotations++;
//     for (int i = 0; i < 4; i++) {
//       oldx = col.at(i);
//       oldy = row.at(i);
//       tempx = oldx - originx;
//       tempy = oldy - originy;
//       if (rotations % 2 == 1) {
//         newx = (0 * tempx) + (-1 * tempy);  // counter clockwise
//         newy = (-1 * tempx) + (0 * tempy);
//       } else {
//         newx = (0 * tempx) + (-1 * tempy);   // clockwise
//         newy = (1 * tempx) + (0 * tempy);
//       }
//       xcopy.at(i) = newx + originx;
//       ycopy.at(i) = newy + originy;
//     }
//     return;
//   } else {
//     for (int i = 0; i < 4; i++) {
//       oldx = xcopy.at(i);  // center of rotation
//       oldy = ycopy.at(i);
//       tempx = oldx - originx;
//       tempy = oldy - originy;
//       newx = (0 * tempx) + (-1 * tempy); // clockwise
//       newy = (1 * tempx) + (0 * tempy);
//       xcopy.at(i) = newx + originx;
//       ycopy.at(i) = newy + originy;
//     }
//   }
//   // correct boundaries until they don't need correction
//   // if (rotateCorrection() == false);
//   row = ycopy;
//   col = xcopy;

//   return;
// }


// void Shape::alignShape() {
//   // Push shape blocks upwards
//   while (all_of(reference.at(0).begin(), reference.at(0).end(), [] (int i) {
//   return i == 0;
// })) {
//     std::rotate(reference.begin(), reference.begin() + 1, reference.end());
//   }

//   // Push shape blocks to the left
//   vector<int> column;
//   do {
//     column = vector<int> (4, 0);
//     for (int i = 0; i < 4; i++) column.at(i) = reference.at(i).at(0);

//     if (all_of(column.begin(), column.end(), [] (int i) {
//     return i == 0;
//   })) {
//       for (int i = 0; i < 4; i++) std::rotate(reference.at(i).begin(),
//                                                 reference.at(i).begin() + 1,
//                                                 reference.at(i).end());
//     }
//   } while (all_of(column.begin(), column.end(), [] (int i) {
//   return i == 0;
// }));

//   for (int i = 0; i < 4; i++) {
//     for (int j = 0; j < 4; j++) {
//       if (reference.at(i).at(j) != '0') {
//         row.at(reference.at(i).at(j)) = i;
//         col.at(reference.at(i).at(j)) = j;
//       }
//     }
//   }
// }


// Draw a shape on the board
void Shape::draw(sf::RenderWindow * window, bool isNext) {
  if (!isNext) {
    for (int i = 0; i < 4; i++) {
      int xPos = col.at(i) * shapeXY;
      int yPos = row.at(i) * shapeXY;

      shapes.at(i).block.setPosition(xPos, yPos);

      window -> draw(shapes.at(i).block);
    }
  } else {
    Shape tempClone = *this;
    for (int i = 0; i < 4; i++) {
      tempClone.shapes.at(i).block.setSize(sf::Vector2f(30, 30));

      int xPos = tempClone.col.at(i) * 30 + 520;
      int yPos = tempClone.row.at(i) * 30 + 310;

      tempClone.shapes.at(i).block.setPosition(xPos, yPos);

      window -> draw(tempClone.shapes.at(i).block);
    }
  }
}












// MAIN FUNCTIONS -------------------------



// Checks all game events
void checkEvents(sf::RenderWindow * window, sf::Event event, Shape *s, Board * b,
                 sf::Sprite pause) {
  while (window -> pollEvent(event)) {
    // Close window
    if (event.type == sf::Event::Closed) exit(1);

    // Keyboard events
    if (event.type == sf::Event::KeyPressed) {
      sf::Keyboard::Key key = event.key.code;
      if (key == sf::Keyboard::R) rotate(s, b);
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

  } else if (ShapeID == 1) { // Z
    row = {0, 0, 1, 1};
    col = {0, 1, 1, 2};
    shapeColor = sf::Color(230, 0, 0);  // red

  } else if (ShapeID == 2) { // S (reverse Z)
    row = {1, 0, 1, 0};
    col = {0, 1, 1, 2};
    shapeColor = sf::Color(215, 50, 235);  // magenta

  } else if (ShapeID == 3) { // L
    row = {0, 0, 0, 1};
    col = {0, 1, 2, 2};
    shapeColor = sf::Color(255, 235, 20);  // yellow

  } else if (ShapeID == 4) { // J (reverse L)
    row = {1, 1, 0, 1};
    col = {0, 1, 2, 2};
    shapeColor = sf::Color(23, 35, 200);  // blue

  } else if (ShapeID == 5) { // O (square)
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

void rotate(Shape *s, Board * b) {
  float angle = 90 * (PI / 180);
  float pivotx = 0, pivoty = 1;
  vector<int> ycopy = s->row;
  vector<int> xcopy = s->col;
  bool possible = true;

  // square doesn't rotate
  if (s->ShapeID == 5) return;
  // line has a different pivot point
  if (s->ShapeID == 4) pivotx = 1;

  // line
  if (s->ShapeID == 0) {

  }
  // set origin to the board values and add back values once it's been rotated

  float a_off_x = xcopy.at(0) - pivotx;
  float b_off_x = xcopy.at(2) - pivotx;
  float c_off_x = xcopy.at(3) - pivotx;
  float a_off_y = ycopy.at(0) - pivoty;
  float b_off_y = ycopy.at(2) - pivoty;
  float c_off_y = ycopy.at(2) - pivoty;

  float ax = pivotx + (a_off_x * cosf(angle) - a_off_y * sinf(angle));
  float ay = pivoty + (a_off_x * sinf(angle) + a_off_y * cosf(angle));
  float bx = pivotx + (b_off_x * cosf(angle) - b_off_y * sinf(angle));
  float by = pivoty + (b_off_x * sinf(angle) + b_off_y * cosf(angle));
  float cx = pivotx + (c_off_x * cosf(angle) - c_off_y * sinf(angle));
  float cy = pivoty + (c_off_x * sinf(angle) + c_off_y * cosf(angle));

  // check collision then add back values
  for (int x = 0; x < boardC; x++) {
    for (int y = 0; y < boardR; y++) {
      for (int i = 0; i < 4; i++) {

        if ((s->reference.at(x).at(xcopy.at(i)) == 1)
            || (ycopy.at(i) + s->reference.at(x).at(y) < 0)
            || (xcopy.at(i) + s->reference.at(x).at(y) > boardR)
            || (ycopy.at(i) + s->reference.at(x).at(y) < 0)) possible = false;
      }
    }
  }
  xcopy.at(0) = ax;
  xcopy.at(2) = bx;
  xcopy.at(3) = cx;
  ycopy.at(0) = ay;
  ycopy.at(2) = by;
  ycopy.at(3) = cy;
}