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

#include <iostream>
#include <fstream>
#include <vector>

std::vector<int> calculateMostCalories(std::fstream& inputFile)
{
    inputFile.open("input.txt");
    if (!inputFile.is_open()) { std::cerr << "File not opened\n"; exit(1); }

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

int main() {
    std::fstream inputFile;
    std::vector<int> values = calculateMostCalories(inputFile);
    int sum = 0;
    for (int i = 0; i < values.size(); i++) {
        sum += values[i];
        std::cout << "Value " << i << ": " << values[i] << std::endl;
    }
    std::cout << "Total sum: " << sum << std::endl;
    return 0;
}
