//
// Created by novot on 07/06/2024.
//

#ifndef SQUARE_H
#define SQUARE_H

#include <cstdint>
#include <utility>
#include <cmath>
#include <iostream>
#include <vector>

#define HeightGrid std::vector<std::vector<Square>>
#define HeightGridText std::vector<std::vector<uint8_t>>

class Square {
public:
    static double calculateDistanceToFinish(const std::pair<int32_t, int32_t>& point, const std::pair<int32_t, int32_t>& finish);
    Square(uint8_t elevation, double distance, int32_t x, int32_t y);
    uint8_t elevation;
    double distance;

    int32_t xCoord;
    int32_t yCoord;

    // Backtracking member variables
    int32_t neighboursVisited;
    bool    beingProcessed;

    bool leftChecked;
    bool rightChecked;
    bool upChecked;
    bool downChecked;



};



#endif //SQUARE_H
