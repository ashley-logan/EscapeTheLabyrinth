#include "EscapeTheLabyrinth.h"
#include "maze.h"
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using std::string;
using std::unordered_map;
using std::unordered_set;
using std::vector;

void FindPath(vector<string> &pathsVector, MazeCell *thisCell, string path,
              unordered_map<string, bool> &itemsFound) {

  bool allowBacktrack = false;

  if (thisCell->whatsHere != "") {
    //
    // TODO if already true, function is looping, end recursion tree
    if (itemsFound[thisCell->whatsHere]) {
      return;
    }

    itemsFound[thisCell->whatsHere] = true;
    allowBacktrack = true;
  }

  if (itemsFound["Spellbook"] && itemsFound["Potion"] && itemsFound["Wand"]) {
    pathsVector.push_back(path);
    return;
  }

  // if(checkCache && cellCache.count(thisCell)) {
  //     return;
  // }

  // cellCache.insert(thisCell);

  char prevMove = allowBacktrack ? '\0' : path.back();

  if (prevMove != 'S' && thisCell->north) {
    path.push_back('N');
    FindPath(thisCell->north, path);
    path.pop_back();
  }
  if (prevMove != 'W' && thisCell->east) {
    path.push_back('E');
    FindPath(thisCell->east, path);
    path.pop_back();
  }
  if (prevMove != 'N' && thisCell->south) {
    path.push_back('S');
    FindPath(thisCell->south, path);
    path.pop_back();
  }
  if (prevMove != 'E' && thisCell->west) {
    path.push_back('W');
    FindPath(thisCell->west, path);
    path.pop_back();
  }
}
MazeCell *MazeCell::*GetMember(const char direction) {
  switch (direction) {
  case 'N':
    return &MazeCell::north;
  case 'E':
    return &MazeCell::east;
  case 'S':
    return &MazeCell::south;
  case 'W':
    return &MazeCell::west;
  default:
    return nullptr;
  }
}

void acquireItem(const string whatsHere, bool &Spellbook, bool &Potion,
                 bool &Wand) {
  if (whatsHere == "Spellbook") {
    Spellbook = true;
  } else if (whatsHere == "Potion") {
    Potion = true;
  } else if (whatsHere == "Wand") {
    Wand = true;
  }
  return;
}

string &LikeLadder(vector<string> &pathsVec, MazeCell *start) {
  bool Spellbook = false, Potion = false, Wand = false;

  string thisPath; // holds the sequence of directions up to the current cell;
  vector<string> pathsList; // holds all currently valid paths
  pathsList.push_back(thisPath);

  MazeCell *thisCell = start;

  while (!pathsList.empty()) {
    thisPath = pathsList.back();
    pathsList.pop_back();

    for (char direction : {'N', 'E', 'S', 'W'}) {
      MazeCell *MazeCell::*memPtr = GetMember(direction);

      if (!memPtr) {
        continue;
      }

      if (thisCell->*memPtr) {
        if (thisCell->*memPtr->whatsHere != "") {
          acquireItem(thisCell->*memPtr->whatsHere, Spellbook, Potion, Wand);
        }

        if (Spellbook && Potion && Wand) {
          thisPath += direction;
          return thisPath;
        }
        thisPath += direction;
        pathsList.push_back(thisPath);
      }
    }
  }
}

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

void PathFinder(string &thisPath, MazeCell *thisCell,
                unordered_set<string> &itemsFound) {
  char lastMove =
      thisPath.empty()
          ? '\0'
          : thisPath.back(); // get the direction of the previous move
  bool allowBacktrack =
      false; // whether or not the next cell can be in the opposite direction of
             // the previous move (backtracking)

  if (!thisCell) {
    // if thisCell is a dead end, do not continue this recursion path
    return;
  }

  if (!thisCell->whatsHere.empty()) {
    // if there is an item in this cell
    if (itemsFound.count(thisCell->whatsHere)) {
      // if this item has already been found, the search is looping; do not
      // continue this recursion path
      return;
    }
    itemsFound.insert(thisCell->whatsHere);
    allowBacktrack = true; // allow backtracking since item found
  }

  if (itemsFound.size() == 3) {
    // all items found, maze complete
    return;
  }

  for (char mv : {'N', 'E', 'S', 'W'}) {
    if (!allowBacktrack && isBacktrack(lastMove, mv)) {
      continue;
    }

    MazeCell *MazeCell::*nextCell = GetMember(mv);

    PathFinder(thisPath.append(mv), thisCell->*nextCell, itemsFound);

    thisPath.pop_back();
  }
}
/*
condition for path to be added to pathsVector:
    Spellbook, Potion, and Wand found
*/
int main() {
  unordered_set<string> itemsFound;
  string finalPath;
  bool allowBacktrack = false;
}