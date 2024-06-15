//
// Created by novot on 09/06/2024.
//

#include "Search.h"
#include "Square.h"

Square* Search::chooseBestSquare(Square& currentSquare, const int32_t mapWidth,
                                const int32_t mapHeight, HeightGrid& heightGrid,
                                int32_t maxElevation, std::vector<Square*> &currentPath) {


    Square* left    = nullptr;
    Square* right   = nullptr;
    Square* up      = nullptr;
    Square* down    = nullptr;


    int32_t     squareX             = currentSquare.xCoord;
    int32_t     squareY             = currentSquare.yCoord;
    int32_t     currentElevation    = currentSquare.elevation;

    if (squareX > 0)                { left  = &heightGrid[squareY][squareX-1]; }
    if (squareX < mapWidth-1)       { right = &heightGrid[squareY][squareX+1]; }
    if (squareY < mapHeight-1)      { down  = &heightGrid[squareY+1][squareX]; }
    if (squareY > 0)                { up    = &heightGrid[squareY-1][squareX]; }

    if (left == nullptr && right == nullptr && up == nullptr && down == nullptr) {
        return nullptr;
    }
    if (currentSquare.leftChecked && currentSquare.rightChecked && currentSquare.upChecked
        && currentSquare.downChecked) {
        return nullptr;
    }


    Square* bestSquare       = nullptr;

    if (!currentSquare.leftChecked) {
        if (!checkIfVisited(currentPath, left)) {
            bestSquare = evalNeighbour(left, bestSquare, &currentSquare, maxElevation);
        }
    }
    if (!currentSquare.rightChecked) {
        if (!checkIfVisited(currentPath, right)) {
            bestSquare = evalNeighbour(right, bestSquare, &currentSquare, maxElevation);
        }
    }
    if (!currentSquare.upChecked) {
        if (!checkIfVisited(currentPath, up)) {
            bestSquare = evalNeighbour(up, bestSquare, &currentSquare, maxElevation);
        }
    }
    if (!currentSquare.downChecked) {
        if (!checkIfVisited(currentPath, down)) {
            bestSquare = evalNeighbour(down, bestSquare, &currentSquare, maxElevation);
        }
    }

    if (bestSquare == left) {
        currentSquare.leftChecked = true;
    }
    else if (bestSquare == right) {
        currentSquare.rightChecked = true;
    }
    else if (bestSquare == up) {
        currentSquare.upChecked = true;
    }
    else if (bestSquare == down) {
        currentSquare.downChecked = true;
    }

    return bestSquare;
}

Square* Search::evalNeighbour(Square* neighbour, Square* currentBest, Square* currentSquare, int32_t maxElevation) {
    double minDistance = 100000;

    if (neighbour == nullptr && currentBest == nullptr) {
        return nullptr;
    }

    if (neighbour == nullptr) {
        return currentBest;
    }

    if (neighbour->elevation == 'E' && currentSquare->elevation == maxElevation) {
        std::cout << "FINISH" << std::endl;
        return neighbour;
    } else if (neighbour->elevation == 'E') {return currentBest;}

    if (currentBest == nullptr) {
        if (neighbour->elevation <= currentSquare->elevation +1) {
            return neighbour;
        } else {
            return nullptr;
        }
    }


    if (neighbour->distance <= currentBest->distance
         && neighbour->elevation <= currentSquare->elevation +1) {
             return neighbour;
         }

    return currentBest;





    // double minDistance = 100000000;
    // if (neighbour == nullptr) {
    //     return currentBest;
    // }
    //
    // if (currentBest == nullptr) {
    //     if (neighbour->elevation <= currentSquare->elevation +1) {
    //         return neighbour;
    //     }
    //     else {
    //         minDistance = currentBest->distance;
    //     }
    // }
    //
    // if (neighbour->elevation == 'E' && currentSquare->elevation == maxElevation) {
    //     return neighbour;
    // } else if (neighbour->elevation == 'E') {return nullptr;}
    //
    // if (neighbour != nullptr && neighbour->distance <= minDistance
    //     && neighbour->elevation <= currentSquare->elevation +1) {
    //         return neighbour;
    //     }
    //
    // return currentBest;
}
bool Search::checkIfVisited(std::vector<Square*>& currentPath, Square* square) {
    for(auto item : currentPath) {
        if (square == item) {
            return true;
        }
    }
    return false;
}
