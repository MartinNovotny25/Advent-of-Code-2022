#include <iostream>
#include <fstream>
#include <vector>

typedef struct returnValues{
    std::vector<int>top3_MostCalories = {0,0,0};
} returnValues;

returnValues calculateMostCalories(std::fstream& inputFile)
{
    inputFile.open("input.txt");
    if (!inputFile.is_open()) { std::cerr << "File not opened\n"; exit(1); }

    int currentCaloriesSum = 0;
    int currentCalories;

    std::string line;

    returnValues returnStruct;

    while(std::getline(inputFile, line)) {
        if (line.empty()) {
            for (int i = 0; i < 3; i++) {
                if (returnStruct.top3_MostCalories[i] < currentCaloriesSum) {
                    returnStruct.top3_MostCalories[i] = currentCaloriesSum;
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
    return returnStruct;
}

int main() {
    std::fstream inputFile;
    returnValues values = calculateMostCalories(inputFile);
    int sum = 0;
    for (int i = 0; i < values.top3_MostCalories.size(); i++) {
        sum += values.top3_MostCalories[i];
        std::cout << "Value " << i << ": " << values.top3_MostCalories[i] << std::endl;
    }
    std::cout << "Total sum: " << sum << std::endl;
    return 0;
}
