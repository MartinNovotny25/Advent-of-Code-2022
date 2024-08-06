//
// Created by novot on 09/06/2024.
//

#ifndef SEARCH_H
#define SEARCH_H

#include <vector>
#include "Square.h"



class Search {
public:
    static Square* chooseBestSquare();
    static Square* evalNeighbour();
    static bool checkIfVisited(std::vector<Square*>& currentPath, Square* square);
};


class Path {
public:
    std::vector<Square*> pathVector;
    std::vector<Square*> closedVector;
};
#endif //SEARCH_H
