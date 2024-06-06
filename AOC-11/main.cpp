#include <iostream>
#include <fstream>
#include <sstream>
#include "Monkey.h"

std::ifstream& operator>>(std::ifstream& is, std::vector<Monkey>& monkeyVector);
int32_t readNumber(std::ifstream& is);
void readStartingItems(std::ifstream& is, Monkey&);
void readOperation(std::ifstream& is, Monkey& monkeyObj);

int main() {
    // Create input stream
    std::ifstream inputStream(R"(C:\Projects\Advent-of-Code-2022\AOC-11\input.txt)");
    if (!inputStream.is_open()) {
        std::cerr << "Can't open input file." << std::endl;
        exit(1);
    }

    std::vector<Monkey> monkeyObjVector;

    // Process the input line by line
    while (inputStream >> monkeyObjVector) {
        if (inputStream.eof()) { break; }

        for (auto monkey: monkeyObjVector) {
            std::cout << monkey.index << std::endl;
        }
    }

    for (int32_t round = 0; round < 10000; ++round) {
        for(Monkey& monkey : monkeyObjVector) {
            monkey.doMonkeyBusiness(monkeyObjVector);
        }

        if (round == 19 || round == 999 || round == 1999) {
            std::cout << "----- ROUND: " << round+1 << std::endl;
            for(Monkey& monkey : monkeyObjVector) {
                std::cout << "Monkey " << monkey.index << " inspected items " << monkey.inspectionCounter << " times.";
                std::cout << std::endl;
            }
        }


    }

    int64_t max1 = 0; int64_t max2 = 0;
    for (Monkey& monkey : monkeyObjVector) {
        std::cout << monkey.inspectionCounter << std::endl;
        if (monkey.inspectionCounter > max1) {
            max2 = max1;
            max1 =  monkey.inspectionCounter;
        } else if (monkey.inspectionCounter > max2) {
            max2 =  monkey.inspectionCounter;
        }
    }
    std::cout << "Result is: " << max1 * max2 << std::endl;
    return 0;
}


std::ifstream& operator>>(std::ifstream& is, std::vector<Monkey>& monkeyVector)
{
    Monkey currentMonkey;

    // Skip 1st word "Monkey"
    is.ignore(256, ' ');

    // Read the index of the monkey
    currentMonkey.index = readNumber(is);

    // Ignor colon
    is.ignore();

    // Skip characters in front of starting items
    is.ignore(256, ':');
    is.ignore(1);
    readStartingItems(is, currentMonkey);

    is.ignore(256, ':');
    is.ignore(1);

    readOperation(is, currentMonkey);

    is.ignore(256, ':');
    is.ignore(1);

    while (!isdigit(is.peek())) {
        is.ignore(1);
    }

    currentMonkey.divisor = readNumber(is);

    while (!isdigit(is.peek())) {
        is.ignore(1);
    }

    currentMonkey.targetMonkeys.first = readNumber(is);

    while (!isdigit(is.peek())) {
        is.ignore(1);
    }
    currentMonkey.targetMonkeys.second = readNumber(is);

    monkeyVector.push_back(currentMonkey);

    return is;
}

int32_t readNumber(std::ifstream& is) {
    std::string number;
    while (true) {
        if(std::isdigit(is.peek())) {
            char tmp;
            is.get(tmp);
            number += tmp;
        } else {
            break;
        }
    }

    return std::strtol(number.c_str(), nullptr, 10);
}

void readStartingItems(std::ifstream& is, Monkey& monkeyObj) {
    while (is.peek() != 10) {
        int32_t monkeyItem = readNumber(is);
        monkeyObj.items.push_back(monkeyItem);

        // Ignore comma and space
        if (is.peek() == ',')   { is.ignore(2); }
    }
}

void readOperation(std::ifstream& is, Monkey& monkeyObj) {
    std::string expString;
    char c;
    while (c != 10) {
        is.get(c);
        while(c != 32 && c != 10) {
            expString += c;
            is.get(c);
        }
        monkeyObj.operation.push_back(expString);
        expString = "";

    }

}