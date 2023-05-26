// Advent of Code, Day 5
// Author: Martin Novotný Mlinárcsik, FIT BUT
// Github: https://github.com/MartinNovotny25
// LinkedIn: https://www.linkedin.com/in/martin-novotn%C3%BD-mlin%C3%A1rcsik-377616242/
// 25.5.2023

#include <iostream>
#include <vector>
#include <fstream>
#include <cstdio>

// Prototypes
int parseColumns(FILE* inputFile);
int parseLines(FILE* inputFile);
char* createArray(int columnsNum, int rowsNum, FILE* inputFile);

#define COLUMN_SPACE  1
#define BRACKETS  2
#define LETTER  1


int main() {
    FILE* inputFile;
    inputFile = fopen("AOC-5/input.txt", "r");
    if (inputFile == NULL) {
        std::cerr << "File not found" << std::endl;
        fclose(inputFile);
    }

    int columnsNum = parseColumns(inputFile);
    int rowsNum = parseLines(inputFile);

    char* array = createArray(columnsNum, rowsNum, inputFile);
    for (int i = 0; i < columnsNum * rowsNum; ++i){
        std::cout << array[i] << " ";
    }




    fclose(inputFile);
    free(array);
}

int parseColumns(FILE* inputFile) {
    int symbol;
    int n = 0;
    do {
        symbol = fgetc(inputFile);
        n++;
    } while (symbol != '\n');

    fseek(inputFile, 0, SEEK_SET);
    return (n >> 2);
}

int parseLines(FILE* inputFile) {
    int symbol = '\0';
    int n = 0;
    while (symbol != '1') {
        symbol = fgetc(inputFile);
        if (symbol == '\n') { n++; }
    }

    fseek(inputFile, 0, SEEK_SET);
    return n;
}

char* createArray(int columnsNum, int rowsNum, FILE* inputFile) {
   char* array = (char*) malloc(columnsNum * rowsNum);
   int symbol = '\0';
   const int num_SymbolsInLine = columnsNum * (LETTER + BRACKETS + COLUMN_SPACE);
   const int letterOffset = BRACKETS + COLUMN_SPACE;

   // Fill the array
   for (int i = 0; i < rowsNum; ++i) {
       fseek(inputFile, i * num_SymbolsInLine, SEEK_SET);
       for (int j = 0; j < columnsNum; ++j) {
           (j == 0) ? fseek(inputFile, 1, SEEK_CUR) : fseek(inputFile, letterOffset, SEEK_CUR);
           symbol = fgetc(inputFile);
           symbol == ' ' ? array[columnsNum * i + j] = '\0' : array[columnsNum * i + j] = char(symbol);
       }
   }
   return array;
}
