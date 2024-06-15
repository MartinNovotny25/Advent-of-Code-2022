//
// Created by novot on 07/06/2024.
//

#include "Square.h"

Square::Square(const uint8_t elevation, const double distance, const int32_t x, const int32_t y) {
    this->distance              = distance;
    this->elevation             = elevation;
    this->xCoord                = x;
    this->yCoord                = y;
    this->neighboursVisited     = 0;
    this->beingProcessed        = false;

    this->leftChecked           = false;
    this->rightChecked          = false;
    this->upChecked             = false;
    this->downChecked           = false;

}

double Square::calculateDistanceToFinish(const std::pair<int32_t, int32_t>& point,
                                         const std::pair<int32_t, int32_t>& finish) {

    double distanceX = std::abs(finish.second - point.second);
    double distanceY = std::abs(finish.first - point.first);

    return static_cast<double>(std::sqrt(std::pow(distanceX, 2) + std::pow(distanceY,2)));
}

void operator<<(std::ostream& os, HeightGrid heightGrid) {
    for (auto line: heightGrid) {
        for (auto tile: line) {
                os << tile.elevation;
            }

            os << std::endl;
        }
}

void printPath( HeightGrid heightGrid, std::vector<Square*> path) {
    for (auto line: heightGrid) {
        for (auto tile: line) {
            bool visited = false;
            for (auto pSquare : path) {
                if (tile.yCoord == pSquare->yCoord && tile.xCoord == pSquare->xCoord) {
                    visited = true;
                    break;
                } else {
                    visited = false;
                    }
                }
            if (visited) {
                std::cout << "#";
            } else {
                std::cout << ".";
            }
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}
