#include "maze.h"
#include <iomanip>
#include <iostream>
#include <string>
#include <unordered_set>
#include <vector>

using std::string;
using std::unordered_set;
using std::vector;

// MazeCell *MazeCell::*GetMember(const char direction) {
//   switch (direction) {
//   case 'N':
//     return &MazeCell::north;
//   case 'E':
//     return &MazeCell::east;
//   case 'S':
//     return &MazeCell::south;
//   case 'W':
//     return &MazeCell::west;
//   default:
//     return nullptr;
//   }
// }

bool isBacktrack(char prevMove, char nextMove) {
  // returns true if prevMove and nextMove are opposites
  switch (nextMove) {
  case 'N':
    return prevMove == 'S';
  case 'E':
    return prevMove == 'W';
  case 'S':
    return prevMove == 'N';
  case 'W':
    return prevMove == 'E';
  default:
    return false;
  }
}

MazeCell *MoveCell(char thisMove, MazeCell *thisCell) {
  switch (thisMove) {
  case 'N':
    return thisCell->north;
  case 'E':
    return thisCell->east;
  case 'S':
    return thisCell->south;
  case 'W':
    return thisCell->west;
  default:
    return nullptr;
  }
}

string PathFinder(char thisMove, MazeCell *thisCell,
                  unordered_set<string> itemsFound, int recursionDepth) {

  std::cout << std::setw(recursionDepth) << std::right << thisMove << std::endl;
  bool allowBacktrack = false;

  if (!thisCell->whatsHere.empty()) {
    if (itemsFound.count(thisCell->whatsHere)) {
      return "";
    }
    itemsFound.insert(thisCell->whatsHere);
    allowBacktrack = true;
  }

  if (itemsFound.size() == 3) {
    return string(1, thisMove);
  }

  for (char mv : {'N', 'E', 'S', 'W'}) {
    if (!allowBacktrack && isBacktrack(thisMove, mv)) {
      // if next move backtracks and backtracking is not allowed, skip move
      continue;
    }

    if (MazeCell *nextCell = MoveCell(mv, thisCell)) {
      // if next cell is not nullptr, check next cell
      string newPath = PathFinder(mv, nextCell, itemsFound, recursionDepth + 1);

      if (newPath != "") {
        return newPath.insert(0, 1, thisMove);
      }
    }
  }

  return "";
}
/*
condition for path to be added to pathsVector:
    Spellbook, Potion, and Wand found
*/
const string netID = "aloga";

int main() {
  Maze m(4, 4);
  MazeCell *start = m.mazeFor(netID);
  unordered_set<string> itemsFound;
  itemsFound.reserve(3);
  string finalPath = PathFinder('\0', start, itemsFound, 1);
  std::cout << "Final Path: " << finalPath << std::endl;
}