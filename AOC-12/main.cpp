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

    heigthGrid[finish.first][finish.second].elevation = maxElevation;

    // Perform search

    std::vector<Path> allPaths;
    Path initPath;
    initPath.pathVector.push_back(&heigthGrid[start.first][start.second]);
    allPaths.push_back(initPath);

    uint32_t bigcounter = 0;

    while (true) {
        bigcounter++;
        int32_t origSize    = 0;
        int32_t addedSize   = 0;

        origSize = allPaths.size();
        std::vector<Path> newPaths;
        std::vector<int32_t> remove;
        int32_t counter = 0;

        for (Path& path : allPaths) {


            Square* lastSquare = path.pathVector.at(path.pathVector.size()-1);
            if (lastSquare == &heigthGrid[finish.first][finish.second]) {
                std::cout << "SIZE: " << path.pathVector.size() << std::endl;
                printPath(heigthGrid, path.pathVector);
                return 0;
            }

            Square* currentSquare = path.pathVector.at(path.pathVector.size()-1);
            int32_t     squareX             = currentSquare->xCoord;
            int32_t     squareY             = currentSquare->yCoord;

            Square* left    = nullptr;
            Square* right   = nullptr;
            Square* up      = nullptr;
            Square* down    = nullptr;

            if (squareX > 0)                { left  = &heigthGrid[squareY][squareX-1]; }
            if (squareX < mapWidth-1)       { right = &heigthGrid[squareY][squareX+1]; }
            if (squareY < mapHeight-1)      { down  = &heigthGrid[squareY+1][squareX]; }
            if (squareY > 0)                { up    = &heigthGrid[squareY-1][squareX]; }

            if (left == nullptr && right == nullptr && up == nullptr && down == nullptr) {
                remove.push_back(counter);
                continue;
            }

            for (int32_t i = 0; i < 4; i++) {
                Path newPath;
                switch (i) {
                    case 0:
                        if (left != nullptr && !Search::checkIfVisited(path.pathVector, left)
                            && left->elevation <= currentSquare->elevation + 1) {
                            newPath = path;
                            newPath.pathVector.push_back(left);
                            newPaths.push_back(newPath);
                            addedSize++;
                            break;
                        } else {
                            left = nullptr;
                            break;
                        }
                    case 1:
                        if (right != nullptr && !Search::checkIfVisited(path.pathVector, right)
                            && right->elevation <= currentSquare->elevation + 1) {
                            newPath = path;
                            newPath.pathVector.push_back(right);
                            newPaths.push_back(newPath);
                            addedSize++;
                            break;
                        }
                        else {
                            right = nullptr;
                            break;
                        }
                    case 2:
                        if (up != nullptr && !Search::checkIfVisited(path.pathVector, up)
                            && up->elevation <= currentSquare->elevation + 1) {
                            newPath = path;
                            newPath.pathVector.push_back(up);
                            newPaths.push_back(newPath);
                            addedSize++;
                            break;
                        }
                        else {
                            up = nullptr;
                            break;
                        }

                    case 3:
                        if (down != nullptr && !Search::checkIfVisited(path.pathVector, down)
                            && down->elevation <= currentSquare->elevation + 1) {
                            newPath = path;
                            newPath.pathVector.push_back(down);
                            newPaths.push_back(newPath);
                            addedSize++;
                            break;
                        }
                        else {
                            down = nullptr;
                            break;
                        }
                }
            }

        }

        for (auto index : remove) {
            allPaths.erase(allPaths.begin(), allPaths.begin() + index);
        }
        origSize = allPaths.size();

        allPaths.insert(allPaths.end(), newPaths.begin(), newPaths.end());
        //std::cout << allPaths.size() << std::endl;
        allPaths.erase(allPaths.begin(), allPaths.begin() + origSize);
        //std::cout << "NEW: " << allPaths.size() << std::endl;

        std::cout << bigcounter << std::endl;
        if (bigcounter % 20 == 0) {
            for (auto path : allPaths) {
                printPath(heigthGrid, path.pathVector);
            }
        }
    }

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


