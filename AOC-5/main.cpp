// Advent of Code, Day 5
// Author: Martin Novotný Mlinárcsik, FIT BUT
// Github: https://github.com/MartinNovotny25
// LinkedIn: https://www.linkedin.com/in/martin-novotn%C3%BD-mlin%C3%A1rcsik-377616242/
// 25.5.2023

#include <iostream>
#include <vector>
#include <fstream>
#include <cstdio>

typedef struct instructionParams {
    int moveFrom;
    int moveTo;
    int amount;
} instructionParams;

// Prototypes
int parseColumns(FILE* inputFile);
int parseLines(FILE* inputFile);
char* createArray(int columnsNum, int rowsNum, FILE* inputFile);
int moveBlocks(char* p_array, int* maxColumnHeights, int* currentHeights, instructionParams instruction, int amount, int colsNum);
int moveCursorToInstructions(FILE* inputFile, int columnsNum, int rowsNum);
int numberOfInstructions(FILE* inputFile);
void printArray(char* p_array, int columnsNum, int rowsNum);
void printArray(char* p_array, int size);
instructionParams getInstruction(FILE* inputFile);
int getStackTop(char* p_array, int skipIndexes, int columnSize);
int* calculateInitialHeight(char* p_array, int columnSize, int columnNum);
int* createMaxColumnHeights(int rowsNum, int columnNum);
char* resizeArray(char** p_oldArray, int* maxColumnHeights, int* columnHeights, int column, int columnNum);
void detectMissingBlock(char* array, int* maxHeights);


#define COLUMN_SPACE  1
#define BRACKETS  2
#define LETTER  1
#define END_LINE  1

#define ASCII_CONSTANT 48
#define SUM_OF_HEIGHTS_INDEX 1
#define MEMORY_BLOCK 5


int main() {

    // Open the file for reading
    FILE* inputFile;
    inputFile = fopen("AOC-5/input.txt", "r");
    if (inputFile == NULL) {
        std::cerr << "File not found" << std::endl;
        fclose(inputFile);
    }

    const int columnsNum = parseColumns(inputFile); // Retrieve the number of columns
    const int rowsNum = parseLines(inputFile); // Retrieve the number of rows

    char* array = createArray(columnsNum, rowsNum, inputFile); // Create array to store crates
    // Create array to store current heights of columns
    int* columnHeights = calculateInitialHeight(array, rowsNum, columnsNum);
    // Create array to store maximum heights of columns
    int* maxColumnHeights = createMaxColumnHeights(rowsNum, columnsNum);

    moveCursorToInstructions(inputFile, columnsNum, rowsNum); // Move cursor to the beginning of instructions

    const int instructionCount = numberOfInstructions(inputFile); // Get the number of instructions
    moveCursorToInstructions(inputFile, columnsNum, rowsNum);

    for (short int i = 0; i < instructionCount; ++i) {;
        instructionParams instruction = getInstruction(inputFile); // Parse the instruction

        // While the current maximum height (memory allocated for the given column) is lower than the current
        // height + the amount of crates that will be placed there, resize the moveTo column
        while (columnHeights[instruction.moveTo] + instruction.amount > maxColumnHeights[instruction.moveTo]) {
            array = resizeArray(&array, maxColumnHeights, columnHeights,
                                instruction.moveTo, columnsNum);
        }

        // Perform the move
        moveBlocks(array, maxColumnHeights,columnHeights, instruction, instruction.amount, columnsNum);
        // Check for errors ion movement
        detectMissingBlock(array, maxColumnHeights);
    }

    printArray(array, maxColumnHeights[columnsNum]); // Prints the final array

    fclose(inputFile);
    //free(array);
    free(columnHeights);
    free(maxColumnHeights);
}

/*
 * Function returns number of columns
 * Every read symbol increases the counter
 * and by dividing the counter by 4,
 * we get the number of letters 1 row;
 */

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

/*
 * Function counts the number rows by
 * counting endline characters
 */

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

/*
 * Function parses 1 instruction line and returns a structure with
 * its parameters.
 */

instructionParams getInstruction(FILE* inputFile) {
    instructionParams instruction;

    int symbol1, symbol2;
    int val = 0;

    // Skips word "move" by advancing the file cursor by 5 characters
    fseek(inputFile, 5, SEEK_CUR);
    symbol1 = fgetc(inputFile);
    symbol2 = fgetc(inputFile);

    // In case the number is double-digit, the first number has to be multiplied by 10 and added to the second number
    // As they are read as single digits, and the cursor will be moved back one character
    if (symbol2 == ' ') { val = symbol1 - ASCII_CONSTANT; fseek(inputFile, -1, SEEK_CUR);}
    else {
        val = 10*(symbol1 - ASCII_CONSTANT) + (symbol2 - ASCII_CONSTANT);
    }

    instruction.amount = val;

    // Skips word "from" by advancing the file cursor by 6 characters, includes whitespaces
    fseek(inputFile, 6, SEEK_CUR);
    symbol1 = fgetc(inputFile);
    symbol2 = fgetc(inputFile);
    if (symbol2 == ' ') { val = symbol1 - ASCII_CONSTANT; fseek(inputFile, -1, SEEK_CUR);}
    else {
        val = 10*(symbol1 - ASCII_CONSTANT) + (symbol2 - ASCII_CONSTANT);
    }

    instruction.moveFrom = val -1;

    // Skips word "to" by advancing the file cursor by 4 characters, includes whitespaces
    fseek(inputFile, 4, SEEK_CUR);
    symbol1 = fgetc(inputFile);
    symbol2 = fgetc(inputFile);
    if (symbol2 == ' ' || symbol2 == '\n') { val = symbol1 - ASCII_CONSTANT; fseek(inputFile, -1, SEEK_CUR);}
    else {
        val = 10*(symbol1 - ASCII_CONSTANT) + (symbol2 - ASCII_CONSTANT);
    }

    instruction.moveTo = val -1;

    fgetc(inputFile);
    return instruction;
}

/*
 * Function moves cursor the to beginning of instructions
 */
int moveCursorToInstructions(FILE* inputFile, int columnsNum, int rowsNum) {
    int offset = ((columnsNum * (BRACKETS + COLUMN_SPACE + LETTER)) * (rowsNum + 1)) + END_LINE;
    fseek(inputFile, offset, SEEK_SET);
    return 0;
}

/*
 * Function counts the number of instructions
 */
int numberOfInstructions(FILE* inputFile) {
    int symbol = '\0';
    int count = 0;
    while (symbol != EOF) {
        symbol = fgetc(inputFile);
        if (symbol == '\n') { count++; }
    }

    fseek(inputFile, 0, SEEK_SET);
    return count;
}
/*
 * Function creates the initial array of size columns * rows. After memory allocation,
 * all indexes are set to NULL. Function then goes through the crates in row order
 * and stores the letters into the array IN COLUMN ORDER, so that
 * columns are stored next to each other.
 */
char* createArray(int columnsNum, int rowsNum, FILE* inputFile) {
   char* array = (char*) malloc(sizeof(char) * columnsNum * rowsNum);
   memset(array, '\0' ,columnsNum * rowsNum);
   char symbol = '\0';
   const int num_SymbolsInLine = columnsNum * (LETTER + BRACKETS + COLUMN_SPACE);
   const int letterOffset = BRACKETS + COLUMN_SPACE;

   // Fill the array
   for (unsigned int i = 0; i < rowsNum; ++i) {
       fseek(inputFile, i * num_SymbolsInLine, SEEK_SET);
       for (unsigned int j = 0; j < columnsNum; ++j) {
           (j == 0) ? fseek(inputFile, 1, SEEK_CUR) : fseek(inputFile, letterOffset, SEEK_CUR);
           symbol = fgetc(inputFile);
           symbol == ' ' ? array[j * rowsNum + i] = '\0' : array[j * rowsNum + i] = char(symbol);
       }
   }
   return array;
}
// Array operation logic
// fromOffset - Index of the block that is being moved
// toOffset - Index of the empty space, to which the block is being moved to

/*
 * Function moves crates between columns.
 * fromOffset is the index of the first block that is being moved
 * toOffset is the index of an empty space, to which a block is being moved
 * moveToSkip and moveFromSkip are values that tell the function how many indexes they have to skip
 * to get to the column that is being altered. These values are used in getStackTop, which will use them to
 * get to the wanted columns and then add the number of NULL values (empty spaces), until it reaches first crate.
 */
int moveBlocks(char* p_array, int* maxColumnHeights, int* currentHeights, instructionParams instruction, int amount, int colsNum) {
    int moveToSkip = 0, moveFromSkip = 0;
    for (int i = 0; i < instruction.moveTo; i++) {
        moveToSkip += maxColumnHeights[i];
    }
    for (int i = 0; i < instruction.moveFrom; i++) {
        moveFromSkip += maxColumnHeights[i];
    }

    int fromOffset = getStackTop(p_array, moveFromSkip, maxColumnHeights[instruction.moveFrom]);
    int toOffset = getStackTop(p_array, moveToSkip, maxColumnHeights[instruction.moveTo]);
    if (toOffset > 0) {toOffset--;}

    // Because columns behave like stacks, the first crate picked up will be on the bottom.
    for (int i = 0; i < amount; ++i) {
       p_array[toOffset - i] = p_array[fromOffset + i];
       p_array[fromOffset + i] = '\0';
    }

    // Update the current sizes of both columns
    currentHeights[instruction.moveTo] += amount;
    currentHeights[instruction.moveFrom] -= amount;
    return 0;
}


/*
 * Function returns a value, that gives the current index, on which the current column begins.
 */
int getStackTop(char* p_array, int skipIndexes, int columnSize) {
    char symbol = '\0';
    for (int i = 0; i < columnSize; i++) {
        symbol = p_array[i + skipIndexes];
        if (symbol >= 'A' && symbol <= 'Z') { return i + skipIndexes; }
    }

    return skipIndexes + columnSize;
}

/*
 * Function resizes the array where the crates are stored by a MEMORY_BLOCK value.
 * Afterwards, it copies the values precede the expanded column.
 * Crates in the expanded column are placed in the back of the column, moved back by
 * MEMORY_BLOCK places. The rest of the array is copied after.
 */
char* resizeArray(char** p_oldArray, int* maxColumnHeights, int* columnHeights, int column, int columnNum) {
    // Create new, expanded array
    char* p_newArray = (char *) malloc( (maxColumnHeights[columnNum] + MEMORY_BLOCK));
    memset(p_newArray, '\0', maxColumnHeights[columnNum] + MEMORY_BLOCK);

    // Memcpy the columns before the expanded column into the new array (excludes column 0)
    // Count the number of bytes that have to be copied before the expanded column.
    int numOfBytesPreCols = 0;
    if (column != 0) {
        for (int i = 0; i < column; ++i) {
            numOfBytesPreCols += maxColumnHeights[i];
        }
        for (int i = 0; i < numOfBytesPreCols; ++i) {
            p_newArray[i] = (*p_oldArray)[i];
        }
    }

    // Memcpy the expanded column
    int numOfBytesExpandedCol = maxColumnHeights[column];
    if (columnHeights[column] != 0) {
        for (int i = 0; i < numOfBytesExpandedCol; ++i) {
            p_newArray[numOfBytesPreCols + MEMORY_BLOCK + i] = (*p_oldArray)[i + numOfBytesPreCols];
        }
    }

    // Memcpy of columns after the column that is being expanded (excludes last column)
    int numOfBytesPostCols = 0;
    if (column != columnNum -1) {
        for (int i = column + 1; i < columnNum; ++i) {
            numOfBytesPostCols += maxColumnHeights[i];
        }

        // Sum of numOfBytesPreCols and numOfBytesExpandedCol (size of the column pre-expansion) to calculate offset for data after the expanded column
        int postExpColOffset = numOfBytesPreCols + numOfBytesExpandedCol;
        for (int i = 0; i < numOfBytesPostCols; ++i) {
            p_newArray[postExpColOffset + MEMORY_BLOCK + i] = (*p_oldArray)[i + postExpColOffset];
        }
    }

    // Free the double pointer
    // Fuck this tbh
//    for (int i = 0; i < maxColumnHeights[columnNum]; ++i) {
//        std::cout << &p_oldArray[i] << std::endl;
//        free(&p_oldArray[i]);
//    }
    //free(*p_oldArray);

    // Update the current maximum heights of both columns.
    maxColumnHeights[column] += MEMORY_BLOCK;
    maxColumnHeights[columnNum] += MEMORY_BLOCK;

    return p_newArray;
}

/*
 * Function creates an array of initial heights of each column and returns a pointer.
 */
int* calculateInitialHeight(char* p_array, int columnSize, int columnNum) {
    int index = 0;
    int* heights = (int*) malloc(sizeof(int) * (columnNum + SUM_OF_HEIGHTS_INDEX));
    memset(heights, 0, sizeof(&heights));
    for (int i = 0; i < (columnNum*columnSize); i = i + columnSize) {
        for (int j = 0; j < columnSize; ++j) {
            p_array[i + j] == '\0' ? : (heights[index]++, heights[columnNum]++);
        }
        index++;
    }

    return heights;
}

/*
 * Function creates an array of maximum heights of each column and returns a pointer.
 */

int* createMaxColumnHeights(int rowsNum, int columnsNum) {
    int* maxColumnHeights = (int*) malloc(sizeof(int) * (columnsNum + SUM_OF_HEIGHTS_INDEX));
    for (int i = 0; i < columnsNum + SUM_OF_HEIGHTS_INDEX; ++i) {
        maxColumnHeights[i] = rowsNum;
    }
    maxColumnHeights[columnsNum] = rowsNum * columnsNum;
    return maxColumnHeights;
}

/*
 * Function for printing arrays.
 */
void printArray(char* p_array, int size) {
    for (int i = 0; i < size; ++i){
        std::cout << p_array[i] << " ";
    }
    std::cout << std::endl;
}

/*
 * Debug function, detects faulty crate movement
 */

void detectMissingBlock(char* array, int* maxHeights) {
    int count = 0;
    for (int i = 0; i < maxHeights[9]; i++) {
        if (array[i] >= 'A' && array[i] <= 'Z') {
            count++;
        }
    }
    if (count != 56) {
        std::cout << "*********** ERROR **************" << std::endl;
        std::cout << "MISSING BLOCKS DETECTED" << std::endl;
        std::cout << "Count: " << count << " Real: " << 56 << std::endl;
        std::cout << "*********** ERROR **************" << std::endl;
        exit(-2);
    }
}




