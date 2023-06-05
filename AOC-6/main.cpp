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
bool initialComparison(char* array, int* skipComparison, int* compareOffset);
void printArray(char* array);
void shiftArray(char* array, char symbol);
bool compare(char* array, int* skipComparison, int* compareOffset);

int main() {
    FILE *inputFile;
    inputFile = fopen("AOC-6/input.txt", "r");
    if (inputFile == nullptr) {
        std::cout << "Input file not found" << std::endl;
    }

    char array[4] = {0};
    char symbol = '\0';
    int skipComparison = 0;
    int counter = 0;
    int compareOffset = 0;

    initialFill(array, inputFile);
    printArray(array);
    counter = 4;
    if (initialComparison(array, &skipComparison, &compareOffset) == true) {
        printArray(array);
        std::cout << "Counter value: " << counter << std::endl;
        return 0;
    }

    std::cout << "Initial skip = " << skipComparison << std::endl;
    std::cout << "Initial look = " << compareOffset << std::endl;
    std::cout << "--------------------------" << std::endl;
    while (symbol != EOF) {
        symbol = fgetc(inputFile);
        counter++;
        shiftArray(array, symbol);
        skipComparison--;
        printArray(array);
        std::cout << "Skip = " << skipComparison << std::endl;
        std::cout << "Look = " << compareOffset << std::endl;
        if (skipComparison == 0) {
            std::cout << "COMPARING" << std::endl;
            if (compare(array, &skipComparison, &compareOffset) == true) {
                printArray(array);
                std::cout << "Counter value: " << counter << std::endl;
                exit(0);
            }
        }
        std::cout << "--------------------------" << std::endl;
    }
    std::cout << "NOT FOUND" << std::endl;
    return 1;
}

bool compare(char* array, int* skipComparison, int* compareOffset) {
    for (int i = 0; i < SLIDING_WINDOW - 1; ++i) {
        //for (int j = i + 1 + *compareOffset; j < SLIDING_WINDOW; ++j) {
        //for (int j = i + 1; j < SLIDING_WINDOW; ++j) {
        int tmp = *compareOffset;
        //for (int j = SLIDING_WINDOW -1, k = 0; j != i && k != *compareOffset; --j, ++k) {
        for (int j = i + 1; j < SLIDING_WINDOW; ++j) {
            if (array[i] == array[j]) {
                std::cout << "Index [" << i << "] matches with symbol [" << j << "]\n";
                *skipComparison = i + 1;
                *compareOffset = i + 1;
                return false;
            }
        }
    }
    *compareOffset = 3;
    return true;
}

void initialFill(char* array, FILE* inputFile) {
    for (int i = 0; i < SLIDING_WINDOW; ++i) {
        array[i] = fgetc(inputFile);
    }
}

bool initialComparison(char* array, int* skipComparison, int* compareOffset) {
    for (int i = 0; i < SLIDING_WINDOW - 1; ++i) {
        for (int j = i + 1; j < SLIDING_WINDOW; ++j) {
            if (array[i] == array[j]) {
                *skipComparison = i + 1;
                *compareOffset = i + 1;
                return false;
            }
        }
    }
    *compareOffset = 3;
    return true;
}

void shiftArray(char* array, char symbol) {
    for (int i = 0; i < SLIDING_WINDOW; ++i) {
        i != SLIDING_WINDOW - 1 ? array[i] = array[i+1] : array[i] = symbol;
    }
}

void printArray(char* array) {
    for(int i = 0; i < SLIDING_WINDOW; ++i) {
        std::cout << "[" << i << "]: " << array[i] << " ";
    }

    std::cout << std::endl;
}