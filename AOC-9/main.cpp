#include <iostream>
#include <utility>
#include <cstdint>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>

#include "Rope.h"

int main() {
    std::ifstream inputStream("C:\\Projects\\Advent-of-Code-2022\\AOC-9\\input.txt");

    // If file not opened, exit
    if (!inputStream.is_open()) {
        std::cerr << "Input file not opened" << std::endl;
        exit(1);
    }

    // Variables for storing input
    std::string currentLine;
    std::string lineToken;
    std::vector <std::string> tokenVector;

    // Control objects
    Head        headObj(std::pair<int32_t, int32_t>(0,0));
    Tail        tailObj(std::pair<int32_t, int32_t>(0,0));

    while(std::getline(inputStream, currentLine, '\n')) {
        std::stringstream lineStream(currentLine);
        while (std::getline(lineStream, lineToken, ' ')) {
            tokenVector.push_back(lineToken);
        }

        const char*     inputDirection  = tokenVector[0].c_str();
        const int32_t&  inputSize       = atoi(tokenVector[1].c_str());


        // Move head in input direction by input size
        headObj.move(inputDirection, inputSize);
        tailObj.chaseHead(headObj);
        tokenVector.clear();

        // std::cout << headObj.currentPosition.first << headObj.currentPosition.second << std::endl;
        // std::cout << tailObj.currentPosition.first << tailObj.currentPosition.second << std::endl;
        // break;
    }

    std::cout << tailObj.visitedVector.size() << std::endl;

    return 0;
}
