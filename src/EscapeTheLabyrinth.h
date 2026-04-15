#include "grid.h"
#include "maze.h"
#include <random>
#include <unordered_set>
#include <unordered_map>
#include <memory>
using namespace std;

/* Change these constants to contain the paths out of your mazes. */
// const string kPathOutOfRegularMaze = "EESESWSW";
// const string kPathOutOfTwistyMaze = "WENSEWSEWE";

void MovePtr(MazeCell *&curr, char c) {
  // return the next position in the maze based on the direction char
  switch (c) {
  case 'N':
    curr = curr->north;
    return;
  case 'E':
    curr = curr->east;
    return;
  case 'S':
    curr = curr->south;
    return;
  case 'W':
    curr = curr->west;
    return;
  default:
    curr = nullptr;
    return;
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

bool isPathToFreedom(MazeCell *start, const string &moves) {

  bool Spellbook = false, Potion = false, Wand = false;
  for (char c : moves) {
    if (!start) {
      return false;
    }
    MovePtr(start, c);
    if (start->whatsHere == "Spellbook") {
      // cout << "Found book!" << endl;
      Spellbook = true;
    } else if (start->whatsHere == "Potion") {
      // cout << "Found potion!" << endl;
      Potion = true;
    } else if (start->whatsHere == "Wand") {
      // cout << "Found wand!" << endl;
      Wand = true;
    }
  }
  // if current position is valid and all 3 items have been acquired, return
  // true, else false
  return start && Spellbook && Potion && Wand;
}

vector<string> ShortestPathFinder(MazeCell *start) {
  // back track check independent of cardinality
  struct Path {
    MazeCell *currCell;
    string pathStr;
    unordered_map<MazeCell *, int> cache;
    shared_ptr<unordered_set<string>> items;
  };
  vector<string> escapePaths;
  size_t minLen = 999;

  // only condition to not check backtrack, is if !isTwisty && prevCellHadItem
  queue<Path> paths;
  paths.push(
      {.currCell = start, .items = make_shared<unordered_set<string>>()});

  while (!paths.empty()) {
    Path thisPath = paths.front();
    paths.pop();

    if (thisPath.pathStr.length() >= minLen) {
      continue;
    }

    for (char mv : {'N', 'E', 'S', 'W'}) {
      if (MazeCell *nextCell = MoveCell(mv, thisPath.currCell)) {

        if (thisPath.cache[nextCell] >= 2) {
          // if this cell has been visited two or more times, prune this path
          continue;
        }

        if (thisPath.items->count(nextCell->whatsHere)) {
          // if this path has already picked up the item here, prune path
          continue;
        }

        Path newPath = {nextCell, thisPath.pathStr + mv, thisPath.cache};
        newPath.cache[thisPath.currCell]++;

        if (!nextCell->whatsHere.empty()) {
          // if cell has a new item, create a deep copy of the current items set
          newPath.items = make_shared<unordered_set<string>>(*thisPath.items);
          // insert the new item
          newPath.items->insert(nextCell->whatsHere);

          if (newPath.items->size() >= 3) {
            // if new items has 3 or more, path found, add path
            minLen = newPath.pathStr.length();
            escapePaths.push_back(newPath.pathStr);
            continue;
          }
        } else {
          // if no changes to items are made, share the set
          newPath.items = thisPath.items;
        }

        // push the new path into the front of the queue
        // std::cout << thisPath.pathStr + mv << "\n";
        paths.push(newPath);
      }
    }
  }
  return escapePaths;
}
