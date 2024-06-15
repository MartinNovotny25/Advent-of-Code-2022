#include <iostream>
#include <fstream>
#include <queue>
#include <sstream>
#include <vector>

#include "Square.h"
#include "Search.h"

std::ifstream& operator>>(std::ifstream& is, HeightGridText& heightGrid);
void operator<<(std::ostream& os, HeightGridText textGrid);
void operator<<(std::ostream& os, HeightGrid heightGrid);
bool operator<(const Square& s1, const Square& s2);
void printQueue(std::priority_queue<Square*> queue);
void printPath( HeightGrid heightGrid, std::vector<Square*> path);
int main() {

    std::ifstream inputStream(R"(C:\Projects\Advent-of-Code-2022\AOC-12\input.txt)");

    // Create 2D matrices
    HeightGridText  textGrid;
    HeightGrid      heigthGrid;

    // Read te input
    while(inputStream >> textGrid) {
        if(inputStream.eof()) { break; }
    }

    // erase whitespace at the end
    textGrid.erase(textGrid.end()-1);

    // Find the positions of S and E
    int32_t mapWidth                    = textGrid[0].size();
    int32_t mapHeight                   = textGrid.size();
    std::pair<int32_t, int32_t> finish;
    std::pair<int32_t, int32_t> start;
    uint8_t maxElevation = 0;
    for (int32_t y = 0; y < mapHeight; ++y) {
        for (int32_t x = 0; x < mapWidth; ++x) {
            if      (textGrid[y][x] == 'S') { start.first = y; start.second = x; textGrid[y][x] = 'a';}
            else if (textGrid[y][x] == 'E') { finish.first = y; finish.second = x; }

            if (textGrid[y][x] > maxElevation && textGrid[y][x] != 'S' && textGrid[y][x] != 'E') { maxElevation = textGrid[y][x];}
        }
    }


    // Create MapGrid with Square class objects
    for (int32_t y = 0; y < mapHeight; ++y) {
        std::vector<Square> emptySquareVector;
        heigthGrid.push_back(emptySquareVector);

        // Vector of current line
        std::vector<Square>& currentLineVector = heigthGrid[y];
        for (int32_t x = 0; x < mapWidth; ++x) {
            double distanceToFinish = Square::calculateDistanceToFinish(finish, std::pair<int32_t, int32_t>(y,x));
            Square tmpSquare(textGrid[y][x], distanceToFinish, x, y);
            currentLineVector.push_back(tmpSquare);
        }
    }

    // Perform search

    std::vector<Square*> currentPath;                    // Vector for maintaining current path and backtracing
    currentPath.push_back(&heigthGrid[start.first][start.second]);

    int32_t stepCounter = 0;
    while (true) {
        //std::cout << "STEP: " << stepCounter << std::endl;
        //printQueue(queue);

        Square*      currentSquare       = currentPath[currentPath.size()-1];
        Square*      prevSquare          = currentPath[currentPath.size()-2];
        int32_t      currentElevation    = currentSquare->elevation;
        int32_t      squareX             = currentSquare->xCoord;
        int32_t      squareY             = currentSquare->yCoord;


        if (currentSquare->elevation == 'E') { std::cout << "DONE" << std::endl; break; }

        Square* nextSquare = nullptr;
        nextSquare = Search::chooseBestSquare(*currentSquare, mapWidth, mapHeight, heigthGrid, maxElevation, currentPath);

        while (nextSquare == nullptr) {
            currentSquare->leftChecked = false;
            currentSquare->rightChecked = false;
            currentSquare->upChecked = false;
            currentSquare->downChecked = false;

            currentPath.erase(currentPath.end()-1);
            currentSquare = currentPath.at(currentPath.size()-1);

            stepCounter--;
            nextSquare = Search::chooseBestSquare(*currentSquare, mapWidth, mapHeight, heigthGrid, maxElevation, currentPath);

        }

        currentPath.push_back(nextSquare);
        printPath(heigthGrid, currentPath);

        stepCounter++;
    }

    std::cout << stepCounter << std::endl;
    return 0;
}



std::ifstream& operator>>(std::ifstream& is, HeightGridText& textGrid) {
    std::vector<uint8_t> currentLineVector;
    while(is.peek() != '\n' && !is.eof()) {
        uint8_t c = is.get();
        currentLineVector.push_back(c);

    }

    is.ignore();
    textGrid.push_back(currentLineVector);

    return is;
}

// For running search, we need to overload '<' operator so that std::priority_queue works properly
bool operator<(const Square& s1, const Square& s2) {
    return s1.distance < s2.distance;
}

void printQueue(std::priority_queue<Square*> queue) {
    std::cout << "Current queue: " << std::endl;
    while (queue.size() > 0) {
        std::cout << "(" << queue.top()->xCoord << ", " << queue.top()->yCoord << ", "
        << queue.top()->neighboursVisited << ", D: " << queue.top()->distance
        << std::endl;
        queue.pop();
    }

}


