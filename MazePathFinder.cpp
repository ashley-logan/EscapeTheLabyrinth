#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include "maze.h"
#include "EscapeTheLabyrinth.h"

using std::string;
using std::vector;
using std::unordered_map;
using std::unordered_set;

void FindPath(vector<string>& pathsVector, MazeCell* thisCell, string path, unordered_map<string,bool>& itemsFound, unordered_set<MazeCell*>& addressCache) {
    if (thisCell->whatsHere != "") {
        // TODO if already true, function is looping, end recursion tree
        if (itemsFound[thisCell->whatsHere]) {
            return;
        }

        itemsFound[thisCell->whatsHere] = true;
    }

    if (itemsFound["Spellbook"] && itemsFound["Potion"] && itemsFound["Wand"]) {
        pathsVector.push_back(path);
        return;
    }

    if (addressCache.count(thisCell)) {
        return;
    }

    addressCache.insert(thisCell);

    if(thisCell->north) {
        path.push_back('N');
        FindPath(thisCell->north, path);
        path.pop_back();
    }
    if(thisCell->east) {
        path.push_back('E');
        FindPath(thisCell->east, path);
        path.pop_back();
    }
    if(thisCell->south) {
        path.push_back('S');
        FindPath(thisCell->south, path);
        path.pop_back();
    }
    if(thisCell->west) {
        path.push_back('W');
        FindPath(thisCell->west, path);
        path.pop_back();
    }
}
/*
condition for path to be added to pathsVector:
    Spellbook, Potion, and Wand found
*/
int main() {
    unordered_map<string, bool> itemsFound = {
        {"Spellbook", false},
        {"Potion", false},
        {"Wand", false}
    };
    unordered_set<MazeCell*> addressCache;
}