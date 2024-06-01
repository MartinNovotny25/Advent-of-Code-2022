#include <iostream>
#include <fstream>

#include "CPU.h"

std::istream& operator>>(std::istream& is, operationStruct& operation);
void operator<<(std::ostream& os, const operationStruct& operation);

int main() {
    std::ifstream inputStream(R"(C:\Projects\Advent-of-Code-2022\AOC-10\input.txt)");
    if (!inputStream.is_open()) {
        std::cerr << "Input file not opened, exiting" << std::endl;
        exit(2);
    }

    // While we still have input
    operationStruct operation;
    CPU cpu;
    while (inputStream >> operation) {
        cpu.executeOperation(operation);
    }

    std::cout << cpu.getTotalSignalStrength() << std::endl;

    return 0;
}

// Overloaded >> operator for reading file input
std::istream& operator>>(std::istream& is, operationStruct& operation) {

    if (is >> operation.opCode) {
        if (operation.opCode == "addx") {
            if (is >> operation.opValue) {
                return is;
            }
        } else if (operation.opCode == "noop") {
            return is;
        } else {
            std::cerr << "Unknown operation encountered." << std::endl;
            exit(3);
        }
    // If reading input fails of end of file is reached
    } else {
        is.setstate(std::ios::failbit);
    }

    return is;
}

// Overloaded << operator for printing operationStruct
void operator<<(std::ostream& os, const operationStruct& operation) {
    if (operation.opCode == "addx") {
        os << operation.opCode << " " << operation.opValue << std::endl;
    } else {
        os << operation.opCode << std::endl;
    }
}
