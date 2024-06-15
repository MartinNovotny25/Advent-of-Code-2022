//
// Created by novot on 09/06/2024.
//

#ifndef SEARCH_H
#define SEARCH_H

#include <vector>
#include "Square.h"



class Search {
public:
    static Square* chooseBestSquare(Square& currentSquare, int32_t mapWidth, int32_t mapHeight, HeightGrid& heightGrid, int32_t maxElevation, std::vector<Square*> &currentPath);
    static Square* evalNeighbour(Square* neighbour, Square* currentBest, Square* currentSquare, int32_t maxElevation);
    static bool checkIfVisited(std::vector<Square*>& currentPath, Square* square);
};

#endif //SEARCH_H
