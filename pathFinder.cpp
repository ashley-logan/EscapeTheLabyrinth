#include "src/EscapeTheLabyrinth.h"
#include "src/args.h"
#include "src/maze.h"

int main(int argc, char *argv[]) {
  Parser parser(argc, argv);
  std::cout << "Using seed " << parser.seedStr << " for the mazes\n";

  Maze m(4, 4);
  MazeCell* start;
  if (parser.isReg()) {
    start = m.mazeFor(parser.seedStr);
  } else {
    start = m.twistyMazeFor(parser.seedStr);
  }
  std::vector<std::string> paths = ShortestPathFinder(start);
  std::cout << "All paths:\n";
  for (string &s : paths) {
    if (isPathToFreedom(start, s)) {
      std::cout << s << std::endl;
    } else {
      std::cout << s << " INVALID PATH\n" << std::endl;
    }
    
  }

}