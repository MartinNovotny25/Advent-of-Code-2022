// Advent of Code, Day 4
// Author: Martin Novotný Mlinárcsik, FIT BUT
// Github: https://github.com/MartinNovotny25
// LinkedIn: https://www.linkedin.com/in/martin-novotn%C3%BD-mlin%C3%A1rcsik-377616242/
// 4.12.2022

// Program implements an algorithm for checking interval overlaps.
// Elfs are grouped up in pairs, each one given an interval (a list of
// cells they have to clean). The goal is to check, if any intervals in the pair overlap
// to reduce workload.

// In Part 1, only intervals that contain the other interval in its entirety are counted.
// (One interval is a subset of the other).
// In Part 2, partial overlaps are counter as well.


#include <iostream>
#include <fstream>
#include <vector>
#include <regex>

int calculatePartTwo(std::fstream& inputFile) {
    std::string line;
    std::regex pairDelimiter{","};
    std::regex rangeDelimiter{"-"};

    int containedRanges = 0;

    while(inputFile >> line) {
        std::vector<std::string> splitLine(std::sregex_token_iterator(line.begin(), line.end(), pairDelimiter, -1), {});
        std::vector<std::string> subString1(std::sregex_token_iterator(splitLine[0].begin(),
                                                                       splitLine[0].end(),
                                                                       rangeDelimiter,
                                                                       -1), {});

        std::vector<std::string> subString2(std::sregex_token_iterator(splitLine[1].begin(),
                                                                       splitLine[1].end(),
                                                                       rangeDelimiter,
                                                                       -1), {});

        int firstElf[2]  = {std::stoi(subString1[0], nullptr), std::stoi(subString1[1], nullptr)};
        int secondElf[2] = {std::stoi(subString2[0], nullptr), std::stoi(subString2[1], nullptr)};

        if      (firstElf[1] >= secondElf[0] && firstElf[0] <= secondElf[1] ) { ++containedRanges; continue; }
        else if (secondElf[1] >= firstElf[0] && secondElf[0] <= firstElf[1] ) { ++containedRanges; continue; }
    }
    return containedRanges;
}

int calculatePartOne(std::fstream& inputFile) {
    std::string line;
    std::regex pairDelimiter{","};
    std::regex rangeDelimiter{"-"};

    int fullyContainedRanges = 0;

    while(inputFile >> line) {
        std::vector<std::string> splitLine(std::sregex_token_iterator(line.begin(), line.end(), pairDelimiter, -1), {});
        std::vector<std::string> subString1(std::sregex_token_iterator(splitLine[0].begin(),
                                                                       splitLine[0].end(),
                                                                       rangeDelimiter,
                                                                       -1), {});

        std::vector<std::string> subString2(std::sregex_token_iterator(splitLine[1].begin(),
                                                                       splitLine[1].end(),
                                                                       rangeDelimiter,
                                                                       -1), {});

        int firstElf[2]  = {std::stoi(subString1[0], nullptr), std::stoi(subString1[1], nullptr)};
        int secondElf[2] = {std::stoi(subString2[0], nullptr), std::stoi(subString2[1], nullptr)};

        if      (firstElf[0] <= secondElf[0] && firstElf[1] >= secondElf[1]) { ++fullyContainedRanges; continue; }
        else if (secondElf[0] <= firstElf[0] && secondElf[1] >= firstElf[1]) { ++fullyContainedRanges; continue; }
    }
    return fullyContainedRanges;
}

int main() {
    std::fstream inputFile;
    inputFile.open("input.txt");

    std::cout << "Number of fully contained ranges is: " << calculatePartOne(inputFile) << std::endl;

    inputFile.close();
    inputFile.open("input.txt");
    std::cout << "Number of partially and fully contained ranges is: " << calculatePartTwo(inputFile) << std::endl;

    inputFile.close();
    return 0;
}
