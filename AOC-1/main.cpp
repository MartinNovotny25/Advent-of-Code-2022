// Advent of Code, Day 1
// Author: Martin Novotný Mlinárcsik, FIT BUT
// Github: https://github.com/MartinNovotny25
// LinkedIn: https://www.linkedin.com/in/martin-novotn%C3%BD-mlin%C3%A1rcsik-377616242/
// 1.12.2022

// Program implements an algorithm that sums the number of calories carried by one elf.
// A .txt file (input.txt) is given as an input, which contains integer values -
// One value per line, where that line represents a "snack" carried by the given elf,
// and the value represents how many calories the snack is worth. Empty line between
// 2 sets of lines represents a new elf with separate "list" of snacks;

// In Part1, algorithm had to find the elf with the highest sum of calories in his snacks.
// Algorithm summed up all caloric values carried by one elf and compared the sum to the largest
// current sum. If the current sum is larger than the current largest sum, the current largest sum is
// replaced by the current sum of calories carried by an elf.

// In Part2, algorithm performs a similar action, but now it has to store the top 3 largest sums of calories.
// The only difference is that now, we store 3 current largest sums (largest at the lowest index) and these values
// are then compared with each individual successive sum.

// Supports sorted and unsorted modes, sorted used std::sort. This has not shown any performance upgrades.
// Second parameter: "sorted" for sorted mode, "unsorted" or empty for unsorted mode.

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

void printHelp()
{
    std::cout << "---- HELP ----" << std::endl;
    std::cout << "./fileName [sorted/unsorted/*empty*]" << std::endl;
    std::cout << "WARNING: -h and [sorted/unsorted/*empty*] CANNOT BE COMBINED" << std::endl;
    std::cout << "---- HELP ----" << std::endl;
}

std::vector<int> calculateMostCaloriesSorted(std::fstream& inputFile)
{
    int currentCaloriesSum = 0;
    int currentCalories;

    std::string line;

    std::vector<int>top3_MostCalories = {0,0,0};
    std::vector<int>elfVec;

    while (std::getline(inputFile, line)){
        if (line.empty()) {
            elfVec.emplace_back(currentCaloriesSum);
            currentCaloriesSum = 0;
            continue;
        }

        currentCalories = std::stoi(line, nullptr, 10);
        currentCaloriesSum += currentCalories;
    }

    std::sort(elfVec.begin(), elfVec.end(), std::greater<int>());

    top3_MostCalories[0] = elfVec[0];
    top3_MostCalories[1] = elfVec[1];
    top3_MostCalories[2] = elfVec[2];

    return top3_MostCalories;
}


std::vector<int> calculateMostCalories(std::fstream& inputFile)
{
    int currentCaloriesSum = 0;
    int currentCalories;

    std::string line;

    std::vector<int>top3_MostCalories = {0,0,0};

    while(std::getline(inputFile, line)) {
        if (line.empty()) {
            for (int i = 0; i < 3; i++) {
                if (top3_MostCalories[i] < currentCaloriesSum) {
                    top3_MostCalories[i] = currentCaloriesSum;
                    break;
                }
            }
            currentCaloriesSum = 0;
            continue;
        }

        currentCalories = std::stoi(line, nullptr, 10);
        currentCaloriesSum += currentCalories;
    }

    inputFile.close();

    return top3_MostCalories;
}

int main(int argc, char** argv) {

    std::string argv1; if (argc >= 2) { argv1 = argv[1]; }
    if (argv1 == "-h") {printHelp(); return 1;}

    std::fstream inputFile;
    inputFile.open("input.txt");
    if (!inputFile.is_open()) { std::cerr << "File not opened\n"; exit(1); }

    if (argv1 == "unsorted" || argc == 1) {
        std::cout << "------ UNSORTED ------" << std::endl;

        std::vector<int> values = calculateMostCalories(inputFile);
        int sum = 0;

        for (int i = 0; i < values.size(); i++) {
            sum += values[i];
            std::cout << "Value " << i << ": " << values[i] << std::endl;
        }

        std::cout << "Total sum: " << sum << std::endl;
    }

    else if (argv1 == "sorted") {
        std::cout << "------ SORTED ------" << std::endl;

        std::vector<int> values = calculateMostCaloriesSorted(inputFile);
        int sum = 0;

        for (int i = 0; i < values.size(); i++) {
            sum += values[i];
            std::cout << "Value " << i << ": " << values[i] << std::endl;
        }

        std::cout << "Total sum: " << sum << std::endl;
    }
    return 0;
}
