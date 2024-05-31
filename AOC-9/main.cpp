#include <iostream>
#include <utility>
#include <cstdint>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>

#include "Rope.h"

void testPrint(Head head, const std::vector<Tail>& tailVector);
void printResult(const Tail tail);

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

    bool part1 = false;

    // Control objects
    Head                headObj(std::pair<int32_t, int32_t>(0,0));
    Tail                tailObj(std::pair<int32_t, int32_t>(0,0));
    std::vector<Tail>   tailVector;

    tailVector.resize(9, Tail(std::pair<int32_t, int32_t>(0,0)));
    tailVector[8].visitedVector.push_back(std::pair<int32_t, int32_t>(0,0));

    while(std::getline(inputStream, currentLine, '\n')) {
        std::stringstream lineStream(currentLine);
        while (std::getline(lineStream, lineToken, ' ')) {
            tokenVector.push_back(lineToken);
        }

        const char*     inputDirection  = tokenVector[0].c_str();
        const int32_t&  inputSize       = atoi(tokenVector[1].c_str());


        // Move head in input direction by input size
        if (part1) {
            for (int32_t i = 0; i < inputSize; ++i) {
                headObj.move(inputDirection);
                tailObj.chaseHead(headObj);
                tailObj.checkIfVisited();
            }
        }

        // Part 2 - move multiple knots one-by-one
        else {
            for (int32_t i = 0; i < inputSize; ++i) {
                headObj.move(inputDirection);

                Tail currentHead(headObj.currentPosition);
                for (auto& currentTail : tailVector) {
                    currentTail.chaseHead(currentHead);
                    currentHead = currentTail;
                }
                // Tail checks if current location was visited before
                tailVector[tailVector.size()-1].checkIfVisited();
            }
        }

        tokenVector.clear();
    }

    std::cout << tailVector[tailVector.size()-1].visitedVector.size() << std::endl;

    return 0;
}

void testPrint(Head head, const std::vector<Tail>& tailVector) {
    std::vector<std::vector<char>> field;
    field.resize(21);
    for(auto& line: field) {
        for(int i = 0; i < 26; ++i) {
            line.push_back('.');
        }
    }


    for (int i = tailVector.size()-1; i >= 0; --i) {
        field[tailVector[i].currentPosition.second][tailVector[i].currentPosition.first] = i+48;
    }

    field[head.currentPosition.second][head.currentPosition.first] = 'H';

    for(auto& line: field) {
        for(auto& item: line) {
            std::cout << item;
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;

}

// These function were used to test print the sample input provided in the task
// Can't be used to print your given task input
void printResult(const Tail tail) {
    bool printDot = true;
    for(int y = 0; y < 21; ++y) {
        for(int i = 0; i < 26; ++i) {
            for (auto visited: tail.visitedVector) {
                if (visited == std::pair<int32_t, int32_t>(i,y)) {
                    std::cout << '#';
                    printDot = false;
                    break;
                }
            }
            if (printDot) {
                std::cout << '.';
            } else {
                printDot = true;
            }
        }
        std::cout << std::endl;
    }


}
