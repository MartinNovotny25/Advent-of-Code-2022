// Advent of Code, Day 6
// Author: Martin Novotný Mlinárcsik, FIT BUT
// Github: https://github.com/MartinNovotny25
// LinkedIn: https://www.linkedin.com/in/martin-novotn%C3%BD-mlin%C3%A1rcsik-377616242/
// 25.5.2023

#include <iostream>
#include <vector>
#include <cstdio>
#include <cstring>

#define SLIDING_WINDOW 4

void initialFill(char* array, FILE* inputFile);
void printArray(char* array);

int main() {
    FILE* inputFile;
    inputFile = fopen("AOC-6/input.txt", "r");
    if (inputFile == nullptr) {
        std::cout << "Input file not found" << std::endl;
    }

    char array[4] = {0};
    printArray(array);
    initialFill(array, inputFile);
    printArray(array);


    return 0;
}

void shiftArray(char* array) {

}

void initialFill(char* array, FILE* inputFile) {
    for (int i = 0; i < SLIDING_WINDOW; ++i) {
        array[i] = fgetc(inputFile);
    }
}

void printArray(char* array) {
    for(int i = 0; i < SLIDING_WINDOW; ++i) {
        std::cout << "[" << i << "]: " << array[i] << std::endl;
    }
}