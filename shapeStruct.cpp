#include "shapeStruct.hpp"
#include "blockStruct.cpp"

    // for (int i = 0; i < 4; i++) {
    //   Block newBlock(color, true);
    //   shapes.push_back(newBlock);
    //   reference.at(r.at(i)).at(c.at(i)) = i;
    // }

// Shape constuctor
Shape::Shape() {
  vector<vector<int>> ref (4, vector<int>(4, 0));
    shapeID = ID; 
    // I 
    if (ID == 0) {
      shapeColor = sf::Color(sf::Color::Red);
      col = {0, 0, 0, 0};
      row= {0, 1, 2, 3};

    }
    // Z
    if (shapeID == 1) {
      shapeColor = sf::Color(sf::Color::Red);

      col = {0, 0, 1, 1};
      row = {0, 1, 1, 2};

    }
    // S (reverse Z)
    if (shapeID == 2) {
      shapeColor = sf::Color(sf::Color::Red);

      col = {1, 0, 1, 0};
       row= {0, 1, 1, 2};
    }

    // L
    if (shapeID == 3) {
      shapeColor = sf::Color(sf::Color::Red);

     col  = {0, 0, 0, 1};
     row  = {0, 1, 2, 2};
    }
    // J (reverse L)
    if (shapeID == 4) {
      shapeColor = sf::Color(sf::Color::Red);

      col = {1, 1, 0, 1};
      row = {0, 1, 2, 2};
    }
    // Q
    if (shapeID == 5) {
      shapeColor = sf::Color(sf::Color::Red);

      col = {0, 0, 1, 1};
      row = {0, 1, 0, 1};
    }
    // T
    if (shapeID == 6) {
      shapeColor = sf::Color(sf::Color::Red);

      row = {0, 0, 1, 0};
      col = {0, 1, 1, 2};
    }

      for (int i = 0; i < 4; i++) {
        Block newBlock(shapeColor, true);
        shapes.push_back(newBlock);
        ref.at(row.at(i)).at(col.at(i)) = i + 1;
        reference = ref;
      }

// // Rotate shape
// void Shape::rotate() {
//   // Get transpose of tile
//   std::reverse(row.begin(), row.end());

//   std::swap(row, col);
  
//   // Align the tile to the top-left
//   // alignShape();
// }

// // Optimize shape position
// void Shape::alignShape() {
//   // Push shape blocks upwards
//   while (all_of(reference.at(0).begin(), reference.at(0).end(), [] (int i) {return i == 0;})) {
//     std::rotate(reference.begin(), reference.begin() + 1, reference.end());
//   }

//   // Push shape blocks to the left
//   vector<int> column;
//   do {
//     column = vector<int> (4, 0);
//     for (int i = 0; i < 4; i++) column.at(i) = reference.at(i).at(0);

//     if (all_of(column.begin(), column.end(), [] (int i) {return i == 0;})) {
//       for (int i = 0; i < 4; i++) std::rotate(reference.at(i).begin(),
//                                               reference.at(i).begin() + 1,
//                                               reference.at(i).end());
//     }
//   } while (all_of(column.begin(), column.end(), [] (int i) {return i == 0;}));

  
//   // Set positions on board
//   for (int i = 0; i < 4; i++) {
//     for (int j = 0; j < 4; j++) {
//       if (reference.at(i).at(j) != '0') {
//         row.at(reference.at(i).at(j)) = i;
//         col.at(reference.at(i).at(j)) = j;
//       }
//     }
//   }
// }


// // Draw a shape on the board
// void Shape::draw(sf::RenderWindow * window) {
//   for (int i = 0; i < 4; i++) {
//     int xPos = col.at(i) * CELLSIZE;
//     int yPos = row.at(i) * CELLSIZE;
    
//     shapes.at(i).block.setPosition(xPos, yPos);
  
//     window -> draw(shapes.at(i).block);
//   }
// }

// // Draw next shape
// void Shape::drawNext(sf::RenderWindow * window) {
//   for (int i = 0; i < 4; i++) {
//     int xPos = (col.at(i) * CELLSIZE) + 480;
//     int yPos = (row.at(i) * CELLSIZE) + 675;
    
//     shapes.at(i).block.setPosition(xPos, yPos);
  
//     window -> draw(shapes.at(i).block);
//   }
}
