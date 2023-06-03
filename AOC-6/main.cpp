// Advent of Code, Day 6
// Author: Martin Novotný Mlinárcsik, FIT BUT
// Github: https://github.com/MartinNovotny25
// LinkedIn: https://www.linkedin.com/in/martin-novotn%C3%BD-mlin%C3%A1rcsik-377616242/
// 25.5.2023

#include <iostream>
#include <vector>
#include <cstdio>
#include <cstring>

#define SLIDING_WINDOW 14

void initialFill(char* array, FILE* inputFile);
bool initialComparison(char* array, int* skipComparison);
void printArray(char* array);
void shiftArray(char* array, char symbol);
bool compare(char* array, int* skipComparison, int* compareOffset);

int main() {
    FILE *inputFile;
    inputFile = fopen("AOC-6/input.txt", "r");
    if (inputFile == nullptr) {
        std::cout << "Input file not found" << std::endl;
    }

    char array[14] = {0};
    char symbol = '\0';
    int skipComparison = 0;
    int counter = 0;
    int compareOffset = 0;

    initialFill(array, inputFile);
    printArray(array);
    counter = 14;
    if (initialComparison(array, &skipComparison) == true) {
        printArray(array);
        std::cout << "Counter value: " << counter << std::endl;
        return 0;
    }
    while (symbol != EOF) {
        symbol = fgetc(inputFile);
        counter++;
        shiftArray(array, symbol);
        printArray(array);
        //if (skipComparison == 0) {
            if (compare(array, &skipComparison, &compareOffset) == true) {
                printArray(array);
                std::cout << "Counter value: " << counter << std::endl;
                exit(0);
            }
       // } //else {skipComparison--; compareOffset--;}
        //    else {skipComparison--;}
    }
    std::cout << "NOT FOUND" << std::endl;
    return 1;
}

bool compare(char* array, int* skipComparison, int* compareOffset) {
    for (int i = 0; i < SLIDING_WINDOW - 1; ++i) {
        //for (int j = i + 1 + *compareOffset; j < SLIDING_WINDOW; ++j) {
        for (int j = i + 1; j < SLIDING_WINDOW; ++j) {
            if (array[i] == array[j]) {
                //*skipComparison = i + 1;
                //*compareOffset = i + 1;
                return false;
            }
        }
    }
    return true;
}

void initialFill(char* array, FILE* inputFile) {
    for (int i = 0; i < SLIDING_WINDOW; ++i) {
        array[i] = fgetc(inputFile);
    }
}

bool initialComparison(char* array, int* skipComparison) {
    for (int i = 0; i < SLIDING_WINDOW - 1; ++i) {
        for (int j = i + 1; j < SLIDING_WINDOW; ++j) {
            if (array[i] == array[j]) {
                //*skipComparison = i + 1;
                return false;
            }
        }
    }
    return true;
}

void shiftArray(char* array, char symbol) {
    for (int i = 0; i < SLIDING_WINDOW; ++i) {
        i != SLIDING_WINDOW - 1 ? array[i] = array[i+1] : array[i] = symbol;
    }
}

void printArray(char* array) {
    for(int i = 0; i < SLIDING_WINDOW; ++i) {
        std::cout << "[" << i << "]: " << array[i];
    }

    std::cout << std::endl;
}