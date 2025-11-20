#include <utility>
#include <random>
#include <set>
#include "grid.h"
#include "maze.h"
using namespace std;

/* Change constant kYourNetID to store your netID 
 *    - your submission will be manually inspected to ensure
 *      you have used the exact string that is your netID
 *    - thus, it is vital you understand what your netID is
 *    - ex: Professor Reckinger's email is scotreck@uic.edu, so
 *          Professor Reckinger's netID is scotreck     
 *    - ex: Student Sparky's email is sspark211@uic.edu, so
 *          Student Sparky's netID is sspark211 
 * WARNING: Once you've set set this constant and started 
 * exploring your maze, do NOT edit the value of kYourNetID. 
 * Changing kYourNetID will change which maze you get back, 
 * which might invalidate all your hard work!
 */
const string kYourNetID = "aloga";

/* Change these constants to contain the paths out of your mazes. */
const string kPathOutOfRegularMaze = "TODO: Replace this string with your path out of the normal maze.";
const string kPathOutOfTwistyMaze = "TODO: Replace this string with your path out of the twisty maze.";

int GetMove (char c) {
    switch (c) {
        case 'N':
          break;
        case 'E':
          break;
        case 'S':
          break;
        case 'W':
          break;
        default:
          break;
        }
        return -1;
}

MazeCell* MovePtr(const MazeCell* curr, char c) {
    // return the next position in the maze based on the direction char
    switch (c) {
        case 'N': return curr->north;
        case 'E': return curr->east;
        case 'S': return curr->south;
        case 'W': return curr->west;
        default: return nullptr;
    }
}

bool isPathToFreedom(MazeCell *start, const string& moves) {

    bool Spellbook = false, Potion = false, Wand = false;
    MazeCell* travMaze = start;
    for (char c : moves) {
        if (!travMaze) {
            return false;
        }
        if (travMaze->whatsHere == "SpellBook") {
            Spellbook = true;
        }
        else if (travMaze->whatsHere == "Potion") {
            Potion = true;
        }
        else if (travMaze->whatsHere == "Wand") {
            Wand = true;
        }
        travMaze = MovePtr(travMaze, c);
    }
    // if current position is valid and all 3 items have been acquired, return true, else false
    return travMaze && Spellbook && Potion && Wand;
    
    
    
}
