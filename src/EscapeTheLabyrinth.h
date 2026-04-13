#include "grid.h"
#include "maze.h"
#include <random>
#include <set>
#include <utility>
using namespace std;

/* Change these constants to contain the paths out of your mazes. */
const string kPathOutOfRegularMaze = "EESESWSW";
const string kPathOutOfTwistyMaze = "WENSEWSEWE";

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
