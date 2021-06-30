// Copyright 2021 Madeline Clare Hain   maddiech@bu.edu
//                Ava Remler            aremler@bu.edu
//                Mallory Gerosa        gerosam@bu.edu
//                Abdulaziz AlMailam    almailam@bu.edu

#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include <iostream>
#include <algorithm>

using namespace std;




const int boardX = 10;
const int boardY = 20;
const int CELLSIZE = 40;
const int GAMESPEED = 3;






// BLOCK STRUCT DEFINITION
struct Block {
  sf::RectangleShape block;
  bool isVisible;
  
  // Block constructor
  Block(sf::Color color, bool visibility) {
    block.setSize((sf::Vector2f(CELLSIZE, CELLSIZE)));
    block.setFillColor(color);
    block.setOutlineThickness(-2);
    block.setOutlineColor(sf::Color::White);
    isVisible = visibility;
  }
};






// SHAPE STRUCT DEFINITION
struct Shape {
  vector<Block> shapes;
  vector<int> row;
  vector<int> col;
  vector<vector<int>> reference;

  sf::Color color;
  
  // Shape constuctor with color and row/col
  Shape(sf::Color Color, vector<int> r, vector<int> c) {
    row = r;
    col = c;
    color = Color;
    
    vector<vector<int>> reference (4, vector<int>(4, 0));
    
    for (int i = 0; i < 4; i++) {
      Block newBlock(Color, true);
      shapes.push_back(newBlock);
      reference.at(r.at(i)).at(c.at(i)) = i;
    }
  };
  
  
  // Helper functions
  void draw(sf::RenderWindow *);
  void drawNext(sf::RenderWindow *);
  void rotate();
  void alignShape();
};










// BOARD STRUCT DEFINITION
struct Board {
  vector<vector<Block>> board;
  int boardWeight;
  vector<int> r;
  vector<int> c;
  
  // Board constructor with invisible blocks
  Board() {
    vector<vector<Block>> content(20, vector<Block>(10, Block(sf::Color::Transparent, false)));
    board = content;
    boardWeight = 0;

    for (int i = 0; i < 10; i++) r.push_back(i);
    for (int i = 0; i < 20; i++) c.push_back(i);
  }
  
  // Helper functions
  void draw(sf::RenderWindow *);
  int updateWeight();
  bool updatePosition(Shape *, int, int);
  void drawNext(Shape *, int, int);
};








// MAIN FUNCTION HEADER
void checkEvents(sf::RenderWindow *, sf::Event, Shape *, Board *);
//Shape getGhost(Board, Shape);







int main() {
  // Window settings
  sf::RenderWindow window(sf::VideoMode(720, 800), "Tetris");
  window.setFramerateLimit(5);
  
  // Setup board
  Board board;
  bool activeShape = true;
  
  // Load fonts and textures for background and game data
  sf::Font font;
  font.loadFromFile("Resources/TetrisFont.ttf");
  
  sf::Texture t;
  t.loadFromFile("Resources/background.png");
  sf::Sprite background(t);
    
  // Keep track of game time, display time, score, and level
  sf::Clock gameClock;
  sf::Text time("999", font, 50);
  time.setPosition(450, 465);
  sf::Time refreshTime;
  sf::Clock refreshClock;  

  sf::Text Score("999", font, 50);
  Score.setPosition(450, 275);
  int score=0;

  sf::Text Level("999", font, 50);
  Level.setPosition(450, 370);
  int level=0;
  
  // Create a next piece
  Shape currentShape(sf::Color::Red, {0, 0, 0, 0}, {0, 1, 2, 3});
  Shape nextShape(sf::Color::Yellow, {0, 0, 0, 0}, {0, 1, 2, 3});
  board.updatePosition(&nextShape, 12, 10);

//  Shape ghost = getGhost(board, currentShape);
  
  // Active/live window
  while (window.isOpen()) {
     // Create a new piece after previus piece is placed
    if (!activeShape) {
      currentShape = nextShape;
      Shape nextShape(sf::Color::Yellow, {0, 0, 0, 0}, {0, 1, 2, 3});
      score+=4;
      activeShape = true;
    }
    
    // Checks all window events
    sf::Event event;
    checkEvents(&window, event, &currentShape, &board);
    
    
    // Update the time
    int timeNum = gameClock.getElapsedTime().asSeconds();
    time.setString(to_string(timeNum));

    // Get the current Level
    int level=timeNum/20;
    Level.setString(to_string(level));

    // Get the current Score
    Score.setString(to_string(score));

    
    refreshTime += refreshClock.restart();
    
    
    // Update piece position
    if (refreshTime.asSeconds() >= GAMESPEED) {
      
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
    
    
    // Draw all elements & display the window
    window.clear();

    window.draw(background);
    window.draw(time);
    currentShape.draw(&window);
    nextShape.drawNext(&window);
//    ghost.draw(&window);
    board.draw(&window);
    window.draw(Score);
    window.draw(Level);
    window.display();
  }
}






// BOARD CLASS FUNCTIONS -------------------------

// Draw visible blocks on board
void Board::draw(sf::RenderWindow * window) {
  for (int i = 0; i < 20; i++) {
    for (int j = 0; j < 10; j++) {
      if (board.at(i).at(j).isVisible) {
        window -> draw(board.at(i).at(j).block);
      }
    }
  }
}


// Get number of blocks
int Board::updateWeight() {
  int count = 0;
  
  for (int i = 0; i < 20; i++) {
    for (int j = 0; j < 10; j++) {
      if (board.at(i).at(j).isVisible) count++;
    }
  }
  
  boardWeight = count;
  return count;
}







// Checks all game events
void checkEvents(sf::RenderWindow * window, sf::Event event, Shape * s, Board * b) {
  while (window -> pollEvent(event)) {
    // Close window
    if (event.type == sf::Event::Closed) window -> close();
    
    // Keyboard events
    if (event.type == sf::Event::KeyPressed) {
      if (event.key.code == sf::Keyboard::R) s -> rotate();
      if (event.key.code == sf::Keyboard::Escape) window -> close();
      if (event.key.code == sf::Keyboard::Right) b -> updatePosition(s, 0, 1);
      if (event.key.code == sf::Keyboard::Left) b -> updatePosition(s, 0, -1);
    }
  }
}






// change position of shape on the board
bool Board::updatePosition(Shape * shape, int offsetR, int offsetC) {
  // check if new position is valid
  for (int i = 0; i < 4; i++) {
    int checkR = (shape -> row.at(i)) + offsetR;
    int checkC = (shape -> col.at(i)) + offsetC;
    
    // Out of board bounds
    if ((checkC > 9) || (checkC < 0)) return false;
    if (checkR > 19) return false;
    
    // Board space is occupied
    if (board.at(checkR).at(checkC).isVisible) return false;
  }
  // Display 4 blocks of shape
  for (int i = 0; i < 4; i++) {
    int currentR = (shape -> row.at(i));
    int currentC = (shape -> col.at(i));

    (shape -> row.at(i)) = currentR + offsetR;
    (shape -> col.at(i)) = currentC + offsetC;
  }
  
  return true;
}













// SHAPE CLASS FUNCTIONS -------------------------

void Shape::rotate() {
  // Get transpose of tile
  std::reverse(row.begin(), row.end());

  std::swap(row, col);
  
  // Align the tile to the top-left
  // alignShape();
}

  
// Optimize shape position
void Shape::alignShape() {
  // Push shape blocks upwards
  while (all_of(reference.at(0).begin(), reference.at(0).end(), [] (int i) {return i == 0;})) {
    std::rotate(reference.begin(), reference.begin() + 1, reference.end());
  }

  // Push shape blocks to the left
  vector<int> column;
  do {
    column = vector<int> (4, 0);
    for (int i = 0; i < 4; i++) column.at(i) = reference.at(i).at(0);

    if (all_of(column.begin(), column.end(), [] (int i) {return i == 0;})) {
      for (int i = 0; i < 4; i++) std::rotate(reference.at(i).begin(),
                                              reference.at(i).begin() + 1,
                                              reference.at(i).end());
    }
  } while (all_of(column.begin(), column.end(), [] (int i) {return i == 0;}));

  
  // Set positions on board
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      if (reference.at(i).at(j) != '0') {
        row.at(reference.at(i).at(j)) = i;
        col.at(reference.at(i).at(j)) = j;
      }
    }
  }
}


// Draw a shape on the board
void Shape::draw(sf::RenderWindow * window) {
  for (int i = 0; i < 4; i++) {
    int xPos = col.at(i) * CELLSIZE;
    int yPos = row.at(i) * CELLSIZE;
    
    shapes.at(i).block.setPosition(xPos, yPos);
  
    window -> draw(shapes.at(i).block);
  }
}


void Shape::drawNext(sf::RenderWindow * window) {
  for (int i = 0; i < 4; i++) {
    int xPos = (col.at(i) * CELLSIZE) + 480;
    int yPos = (row.at(i) * CELLSIZE) + 675;
    
    shapes.at(i).block.setPosition(xPos, yPos);
  
    window -> draw(shapes.at(i).block);
  }
}
