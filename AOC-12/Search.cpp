//
// Created by novot on 09/06/2024.
//

#include "Search.h"
#include "Square.h"

Square* Search::chooseBestSquare() {

}

Square* Search::evalNeighbour() {

}
bool Search::checkIfVisited(std::vector<Square*>& currentPath, Square* square) {
    for(auto item : currentPath) {
        if (square == item) {
            return true;
        }
    }
    return false;
}
