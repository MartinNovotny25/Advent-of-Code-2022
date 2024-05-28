// Advent of Code, Day 7
// Author: Martin Novotný Mlinárcsik, FIT BUT
// Github: https://github.com/MartinNovotny25
// LinkedIn: https://www.linkedin.com/in/martin-novotn%C3%BD-mlin%C3%A1rcsik-377616242/
// 26.5.2024


#include <iostream>
#include <cstdio>
#include <map>
#include <unordered_map>
#include <vector>
#include <cstdint>

#include <sstream>
#include <fstream>
#include <stack>
#include <algorithm>

void removeDuplicates(std::string input);

int main() {
    std::ifstream inputStream("C:\\Projects\\Advent-of-Code-2022\\AOC-7\\input.txt");

     // Maps for tracking
     // Ordered map for directory tree structure
     // Unordered map for sizes
     std::unordered_map<std::string, std::pair<int16_t, std::vector<std::string>>> directoryTree;
     std::unordered_map<std::string, int32_t> directorySize;
     std::unordered_map<std::string, std::stack<std::string>> occurencesStack;
     std::unordered_map<std::string, int8_t> occurences;


     directoryTree["/"].first = 0;
     directorySize["/"];

     occurencesStack["/"];
     occurences["/"] = 1;

     std::string currentLine;
     std::string currentDirectory;
     std::vector<std::string> tokens;
     bool list_flag = false;
     int16_t maxNestLevel = 0;
     int16_t currentNestLevel = 0;

     char diffCounter = 33;

     while (std::getline(inputStream, currentLine, '\n')) {

         std::stringstream lineStream(currentLine);
         std::string token;
         while (std::getline(lineStream, token, ' ')) {
             tokens.push_back(token);
         }

         // Execute commands
         if (tokens.at(0) == "$") {

             list_flag = false;
             // If cd, change the current directory so we can assign child directories to it
             if (tokens.at(1) == "cd") {
                // If cd .., we move to the precedessor directory
                if (tokens.at(2) == "..") {
                     for (auto dir: directoryTree) {
                         if (dir.second.first == currentNestLevel -1) {
                             if (std::count(dir.second.second.begin(), dir.second.second.end(), currentDirectory) == 1) {
                                 currentDirectory = dir.first;
                                 currentNestLevel--;
                             }
                         }
                     }
                 }

                // We need to check if the current directory has occured previously and if
                // it already has an alias assigned

                // If this is the first occurence of this directory name, we don't need to use alias
                else if (occurences[tokens.at(2)] == 1) {
                    currentDirectory = tokens.at(2);
                    occurences[tokens.at(2)]++;
                }

                // Else alias has to be used to access correct data values
                else {
                    currentDirectory = occurencesStack[tokens.at(2)].top();
                    occurencesStack[tokens.at(2)].pop();
                }
             }

             // List all subdirectories, set list_flag to true
             else if (tokens.at(1) == "ls") {
                 list_flag = true;
             }

             // Clear the token vector
             tokens.clear();
         }

         // Traverse the printed list
         else if (list_flag) {
             // Add the directories to maps
             if (tokens.at(0) == "dir") {

                 currentNestLevel = directoryTree.at(currentDirectory).first + 1;
                 if (currentNestLevel > maxNestLevel) { maxNestLevel = currentNestLevel; }

                 // This is the first occurence of this directory name, no need for alias
                 if (occurences.find(tokens.at(1)) == occurences.end()) {
                     directoryTree[tokens.at(1)].first = currentNestLevel;
                     directorySize[tokens.at(1)] = 0;
                     directoryTree[currentDirectory].second.push_back(tokens.at(1));

                     // Input the alias into the stack map
                     occurencesStack[tokens.at(1)];

                     // Mark the first occurence
                     occurences[tokens.at(1)] = 1;
                 }

                 // This directory name has already occured, we need a new key to input into the map
                 else {
                     // Create a new alias for the directory by adding a symbol
                     std::string directoryAlias = tokens.at(1) + diffCounter;
                     diffCounter++;

                     // Add dir to the tree under new alias
                     directoryTree[directoryAlias].first = currentNestLevel;
                     directorySize[directoryAlias] = 0;
                     directoryTree[currentDirectory].second.push_back(directoryAlias);

                     // Push the alias into the stack of occurences next to its original name
                     occurencesStack[tokens.at(1)].push(directoryAlias);
                 }
             }

             // Else, the current line only contains a file, so we add its size to the directory size
             else {
                 directorySize[currentDirectory] += std::atoi(tokens.at(0).c_str());
             }
         }
         tokens.clear();
     }

    // If their nestLevel is equal to current maxNestLevel, their values are to be propagated up
     maxNestLevel -= 1;
     while (maxNestLevel > -1) {
         for (const auto& dir : directoryTree) {
             if (dir.second.first == maxNestLevel) {
                 for(const auto& subdir : dir.second.second) {
                     directorySize[dir.first] += directorySize[subdir];
                 }
             }
         }
         maxNestLevel--;
     }

     std::cout << std::endl;

    // If the directory size is less than 100000, add it to the totalSum, which is the output
     int32_t totalSum = 0;
     for(const auto& dir : directoryTree) {
         if (directorySize[dir.first] < 100000) {
             totalSum += directorySize[dir.first];
         }
     }

    // Print the result
     std::cout << totalSum << std::endl;

     return 0;
}