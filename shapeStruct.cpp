#include <utility>
#include "shapeStruct.hpp"
#include <SFML/Graphics.hpp>
using namespace std;

Shape::Shape(sf::Color Color, vector<int> r, vector<int> c) {
  color = Color;
  row = r;
  col = c;
  rotations = 0;
  ShapeID = rand() % 6;

  vector<vector<int>> reference(4, vector<int>(4, 0));

  for (int i = 0; i < 4; i++) {
    Block newBlock(Color, true);
    shapes.push_back(newBlock);
    reference.at(r.at(i)).at(c.at(i)) = i + 1;
  }
}

void Shape::draw(sf::RenderWindow * window, bool isNext) {
  if (!isNext) {
    for (int i = 0; i < 4; i++) {
      int xPos = col.at(i) * CELLSIZE;
      int yPos = row.at(i) * CELLSIZE;

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

void Shape::rotate() {
  // Get transpose of tile
  int rotations = 0;
  if (ShapeID == 5) return;
  int ulr = row.at(0);
  int ulc = col.at(0);
  vector<int> rowcopy, colcopy;
  colcopy = col;
  rowcopy = row;
  std::swap(rowcopy, colcopy);
  std::reverse(colcopy.begin(), colcopy.end());
  std::reverse(rowcopy.begin(), rowcopy.end());

  if (ulr != rowcopy.at(0)) {
    int rowdif = ulr - rowcopy.at(0);
    for (int i = 0; i < rowcopy.size(); i++) {
      rowcopy.at(i) = rowcopy.at(i) + rowdif;
    }
  }
  if (ulc != colcopy.at(0)) {
    int coldif = ulc - colcopy.at(0);
    for (int i = 0; i < colcopy.size(); i++) {
      colcopy.at(i) = colcopy.at(i) + coldif;
    }
  }
  for (int i = 0; i < rowcopy.size(); i++) {
    if ((rowcopy.at(i) < 0) || (rowcopy.at(i) > BOARDR)) {
      rowcopy = row;
      colcopy = col;
    }
  }
  for (int i = 0; i < colcopy.size(); i++) {
    if ((colcopy.at(i) < 0) || (colcopy.at(i) > BOARDC)) {
      colcopy = col;
      rowcopy = row;
    }
  }
  col = colcopy;
  row = rowcopy;
}

// Optimize shape position
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
