// Advent of Code, Day 3
// Author: Martin Novotný Mlinárcsik, FIT BUT
// Github: https://github.com/MartinNovotny25
// LinkedIn: https://www.linkedin.com/in/martin-novotn%C3%BD-mlin%C3%A1rcsik-377616242/
// 3.12.2022

// Program implements algorithm for searching letters in a string. In this puzzle, each elf carries a
// list of items (represented by a string, where 1 item is represented by 1 letter) in a rucksack.
// Only acceptable letters are a-z and A-Z, where a-z have values of 1-26 and A-Z have values of 27-52.
// This rucksack is divided into 2 compartments. It is given, that a given item type can only be
// stored in the same rucksack compartment (e.g. if compartment 1 contains item of type 'A', compartment 2
// should not contain item type 'A' and vice versa).

// In Part 1, algorithm searches each elf and checks if his rucksack contains items of 1 item type in both
// compartments. The value of this item type is then returned and added to a sum of values of all wrongly placed items.
// The sum is the puzzle answer to Part 1.

// In Part 2, elves are grouped in groups of 3 and all carry a common item of a given type
// (serves as "identification badge").
// Algorithm searches for item types that all 3 elves have in common.
// When such item type is found, it's value is returned and added to the sum of values of all identification item types.
// The sum is the puzzle answer to Part 2.

// To calculate values of item types, ASCII values of letters are used. A constant is subtracted from these numeric
// values, which results in the values specified in the task.

#include <iostream>
#include <fstream>
#include <unordered_map>

#define LOWERCASE_CONSTANT  96
#define UPPERCASE_CONSTANT 38

int calculatePartTwo(std::string elfGroup[]) {
    std::unordered_map<char, int> letterOccurrences;

    const char* charLine = elfGroup[0].c_str();
    for(int i = 0; i < elfGroup[0].length(); ++i) {
        if (letterOccurrences.find(charLine[i]) == letterOccurrences.end()) {
            letterOccurrences.insert({charLine[i], 1});
        }
    }

    charLine = elfGroup[1].c_str();
    for (int j = 0; j < elfGroup[1].length(); ++j) {
        if (letterOccurrences.find(charLine[j]) != letterOccurrences.end() && (letterOccurrences.at(charLine[j]) == 1)) {
            ++letterOccurrences.at(charLine[j]);
        }
    }

    charLine = elfGroup[2].c_str();
    for (int j = 0; j < elfGroup[2].length(); ++j) {
        if (letterOccurrences.find(charLine[j]) != letterOccurrences.end() && (letterOccurrences.at(charLine[j]) == 2)) {
            ++letterOccurrences.at(charLine[j]);
        }
    }

    for (auto& [letter, count] : letterOccurrences) {
        if      (count == 3 && letter >= 'a' && letter <= 'z') { return (letter - LOWERCASE_CONSTANT); }
        else if (count == 3 && letter >= 'A' && letter <= 'Z') { return (letter - UPPERCASE_CONSTANT); }
        else                                                   { continue; }
    }

    return NULL;
}

int calculatePartOne(std::string& line) {
    std::unordered_map<char, int> letterOccurrences;
    int sum = 0;

    const char* charLine = line.c_str();
    for(int i = 0; i < line.length()/2; ++i) {
        if (letterOccurrences.find(charLine[i]) == letterOccurrences.end()) {
            letterOccurrences.insert({charLine[i], 1});
        } else  { letterOccurrences.at(charLine[i])++; }
    }

    for(int i = static_cast<int>(line.length())/2; i < line.length(); i++) {
        if (letterOccurrences.find(charLine[i]) != letterOccurrences.end()) {
            if (charLine[i] >= 'a' && charLine[i] <= 'z') {
                sum += charLine[i] - LOWERCASE_CONSTANT;
                break;
            }

            else if (charLine[i] >= 'A' && charLine[i] <= 'Z') {
                sum += charLine[i] - UPPERCASE_CONSTANT;
                break;
            }
        }
    }
    return sum;
}

int main() {
    std::fstream inputFile;
    inputFile.open("input.txt");
    if (!inputFile.is_open()) { std::cerr << "Input file not opened, exiting" << std::endl; exit(1); }

    // Part One
    std::string line;
    long int overallSum = 0;

    while (inputFile >> line) {
        overallSum += calculatePartOne(line);
    }

    std::cout << "Overall sum is: " << overallSum << std::endl;
    overallSum = 0;

    // Part Two
    int lineCounter = 0;
    std::string elfGroup[3];

    inputFile.close();
    inputFile.open("input.txt");
    while (std::getline(inputFile, line)) {
        if (lineCounter < 3) { elfGroup[lineCounter] = line; ++lineCounter; }
        if (lineCounter == 3) { lineCounter = 0; overallSum += calculatePartTwo(elfGroup); }
    }

    std::cout << "Sum of badges is: " << overallSum << std::endl;
    inputFile.close();
    return 0;
}
