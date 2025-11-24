#include "maze.h"
#include <iomanip>
#include <iostream>
#include <memory>
#include <queue>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using std::queue;
using std::shared_ptr;
using std::string;
using std::unordered_map;
using std::unordered_set;
using std::vector;

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

/* Parameter keyword/symbols:
  const T = read-only by value (copy)
  T& = read-and-write by reference (no-copy)
  const T& = read-only by reference (no-copy)
  const T* = pointer read-and-write; data read-only
  T* const = pointer read-only; data read-and-write
  const T* const = pointer read-only; data read-only
*/
string PathFinder(MazeCell *start, bool isTwisty = false) {
  // back track check independent of cardinality
  struct Path {
    MazeCell *currCell;
    string pathStr;
    unordered_map<MazeCell *, int> cache;
    shared_ptr<unordered_set<string>> items;
  };

  // only condition to not check backtrack, is if !isTwisty && prevCellHadItem
  queue<Path> paths;
  paths.push(
      {.currCell = start, .items = make_shared<unordered_set<string>>()});

  while (!paths.empty()) {
    Path thisPath = paths.front();
    paths.pop();

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
            // if new items has 3 or more, path found, return path
            return newPath.pathStr;
          }
        } else {
          // if no changes to items are made, share the set
          newPath.items = thisPath.items;
        }

        // push the new path into the front of the queue
        paths.push(newPath);
      }
    }
  }
  return "";
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
        std::cout << thisPath.pathStr + mv << "\n";
        paths.push(newPath);
      }
    }
  }
  return escapePaths;
}

void ShortestTwistyPathFinder(MazeCell *thisCell, vector<string> &paths,
                              string thisPath = string(1, '\0'),
                              unordered_map<MazeCell *, int> ptrCache = {},
                              unordered_set<string> itemsFound = {},
                              int recursionDepth = 1) {
  static size_t minLen = 999;
  std::cout << std::setw(recursionDepth) << std::right << thisPath.back()
            << std::endl;

  if (thisPath.length() > minLen) {
    return;
  }

  if (ptrCache[thisCell] >= 2) {
    return;
  }

  ptrCache[thisCell] = (ptrCache.count(thisCell)) ? ++ptrCache[thisCell] : 1;

  if (!thisCell->whatsHere.empty()) {
    if (itemsFound.count(thisCell->whatsHere)) {
      return;
    }
    itemsFound.insert(thisCell->whatsHere);
  }

  if (itemsFound.size() == 3) {
    paths.push_back(thisPath);
    minLen = thisPath.length();
    ptrCache.clear();
    std::cout << std::setw(recursionDepth) << std::right << "Found path"
              << std::endl;
    return;
  }

  for (char mv : {'N', 'E', 'S', 'W'}) {

    if (MazeCell *nextCell = MoveCell(mv, thisCell)) {
      // if next cell is not nullptr, check next cell

      thisPath += mv;
      ShortestTwistyPathFinder(nextCell, paths, thisPath, ptrCache, itemsFound,
                               recursionDepth + 1);
      thisPath.pop_back();
    }
  }
  return;
}

const string netID = "aloga";

int main() {
  Maze m(4, 4);
  MazeCell *startReg = m.mazeFor(netID);
  MazeCell *startTwisty = m.twistyMazeFor(netID);
  vector<string> allRegPaths = ShortestPathFinder(startReg);
  vector<string> allTwistyPaths = ShortestPathFinder(startTwisty);
  std::cout << "All regular paths: \n";
  for (string path : allRegPaths) {
    std::cout << path << "\n";
  }
  std::cout << "All twisty paths: \n";
  for (string path : allTwistyPaths) {
    std::cout << path << "\n";
  }
}