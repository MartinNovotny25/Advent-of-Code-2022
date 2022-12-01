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
