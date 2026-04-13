#include "src/EscapeTheLabyrinth.h"
#include "src/grid.h"
#include "src/maze.h"
#include <map>
#include <set>
#include <sstream>
#include <vector>
using namespace std;

int main() {
  Maze m(4, 4);
  MazeCell *start = m.mazeFor(kYourNetID);

  // Put your break point here!

  if (isPathToFreedom(start, kPathOutOfRegularMaze)) {
    cout << "You escaped!" << endl;
  } else {
    cout << "You have not escaped!" << endl;
  }

  return 0;
}