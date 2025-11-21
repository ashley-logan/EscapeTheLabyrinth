#include "maze.h"
#include <iomanip>
#include <iostream>
#include <string>
#include <unordered_set>
#include <unordered_map>
#include <vector>

using std::string;
using std::unordered_set;
using std::unordered_map;
using std::vector;


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

/* Parameter keyword/symbols:
  const T = read-only by value (copy)
  T& = read-and-write by reference (no-copy)
  const T& = read-only by reference (no-copy)
  const T* = pointer read-and-write; data read-only
  T* const = pointer read-only; data read-and-write
  const T* const = pointer read-only; data read-only
*/


void ShortestPathFinder(MazeCell *thisCell, vector<string>& paths, string thisPath = string(1, '\0'), unordered_set<string> itemsFound = {}, int recursionDepth = 1) {
  static size_t minLen = 999;
  std::cout << std::setw(recursionDepth) << std::right << thisPath.back() << std::endl;
  bool allowBacktrack = false;

  if (thisPath.length() > minLen) {
    return;
  }

  if (!thisCell->whatsHere.empty()) {
    if (itemsFound.count(thisCell->whatsHere)) {
      return;
    }
    itemsFound.insert(thisCell->whatsHere);
    allowBacktrack = true;
  }

  if (itemsFound.size() == 3) {
    paths.push_back(thisPath);
    minLen = thisPath.length();
    std::cout << std::setw(recursionDepth) << std::right << "Found path" << std::endl;
    return;
  }

  for (char mv : {'N', 'E', 'S', 'W'}) {
    if (!allowBacktrack && isBacktrack(thisPath.back(), mv)) {
      // if next move backtracks and backtracking is not allowed, skip move
      continue;
    }

    if (MazeCell *nextCell = MoveCell(mv, thisCell)) {
      // if next cell is not nullptr, check next cell

      thisPath += mv;
      ShortestPathFinder(nextCell, paths, thisPath, itemsFound, recursionDepth + 1);
      thisPath.pop_back();

    }
  }
  return;
}

void ShortestTwistyPathFinder(MazeCell *thisCell, vector<string>& paths, string thisPath = string(1, '\0'), unordered_map<MazeCell*, int> ptrCache = {}, unordered_set<string> itemsFound = {}, int recursionDepth = 1) {
  static size_t minLen = 999;
  std::cout << std::setw(recursionDepth) << std::right << thisPath.back() << std::endl;

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
    std::cout << std::setw(recursionDepth) << std::right << "Found path" << std::endl;
    return;
  }

  for (char mv : {'N', 'E', 'S', 'W'}) {

    if (MazeCell *nextCell = MoveCell(mv, thisCell)) {
      // if next cell is not nullptr, check next cell

      thisPath += mv;
      ShortestTwistyPathFinder(nextCell, paths, thisPath, ptrCache, itemsFound, recursionDepth + 1);
      thisPath.pop_back();

    }
  }
  return;
}

string TwistyPathFinder(MazeCell *thisCell, char thisMove = '\0', unordered_map<MazeCell*, int> ptrCache = {}, unordered_set<string> itemsFound = {}, int recursionDepth = 1) {
  // static size_t minLen = 999;
  std::cout << std::setw(recursionDepth) << std::right << thisMove << std::endl;

  if (ptrCache[thisCell] >= 2) {
    return "";
  }

  ptrCache.count(thisCell) ? ptrCache[thisCell]++ : ptrCache[thisCell] = 1;

  if (!thisCell->whatsHere.empty()) {
    if (itemsFound.count(thisCell->whatsHere)) {
      return "";
    }
    itemsFound.insert(thisCell->whatsHere);
  }

  if (itemsFound.size() == 3) {
    return string(1, thisMove);
  }

  for (char mv : {'N', 'E', 'S', 'W'}) {
    if (MazeCell *nextCell = MoveCell(mv, thisCell)) {
      // if next cell is not nullptr, check next cell


      string path = TwistyPathFinder(nextCell, mv, ptrCache, itemsFound, recursionDepth + 1);
      if (!path.empty()) {
        return string(1, thisMove) + path;
      }

    }
  }
  return "";
}

string GetPath(MazeCell* start) {
  vector<string> paths;
  ShortestPathFinder(start, paths);

  string shortestPath = paths.at(0);
  for (string& path : paths) {
    if (path.length() < shortestPath.length()) {
      shortestPath = path;
    }
  }
  return shortestPath;
}

vector<string> GetTwistyPath(MazeCell* start) {
  vector<string> paths;
  ShortestTwistyPathFinder(start, paths);

  return paths;
}

const string netID = "aloga";
int main() {
  Maze m(4, 4);
  // MazeCell *start = m.mazeFor(netID);
  MazeCell* start = m.twistyMazeFor(netID);
  // string finalPath = TwistyPathFinder(start);
  vector<string> paths = GetTwistyPath(start);
  for (string& path : paths) {
    std::cout << "Path: " << path << std::endl;
  }
  // std::cout << "Final Path: " << finalPath << std::endl;
}