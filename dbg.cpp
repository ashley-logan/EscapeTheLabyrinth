// #include "src/EscapeTheLabyrinth.h"
// #include "src/grid.h"
#include "src/maze.h"
#include "src/args.h"


int main(int argc, char *argv[]) {
  Parser parser(argc, argv);
  std::cout << "Using seed " << parser.seedStr << " for the mazes\n";

  Maze m(4, 4);
  MazeCell* start;

  if (parser.isTwisty()) {
    start = m.twistyMazeFor(parser.seedStr);
  } else {
    start = m.mazeFor(parser.seedStr);
  }

  std::cout << "This should print before breakpoint\n";
  // add breakpoint here
  std::cout << "This should print after breakpoint\n";

}