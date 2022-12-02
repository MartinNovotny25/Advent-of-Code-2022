// Advent of Code, Day 2
// Author: Martin Novotný Mlinárcsik, FIT BUT
// Github: https://github.com/MartinNovotny25
// LinkedIn: https://www.linkedin.com/in/martin-novotn%C3%BD-mlin%C3%A1rcsik-377616242/
// 12.2.2022

// Program implements decision-making when playing a game of "Rock, Paper, Scissors" according to a given
// strategy plan. An input file, which is given, is a .txt file that contains 2 columns:
// First column presents choice of you opponent, second column presents your choice, where, depending on
// the part that is being solved, has 2 meanings:

// In Part1, second column symbolizes moves that you make, according to the plan:
// -- X means ROCK, Y means PAPER, Z means SCISSORS

// In Part2, second column symbolizes the OUTCOME that you must achieve:
// -- X means LOSS, Y means DRAW, Z means WIN

#include <iostream>
#include <fstream>

#define ROCK 1 // A, X
#define PAPER 2 // B, Y
#define SCISSORS 3 // C, Z

#define LOSS 0
#define DRAW 3
#define WIN 6

int calculatePart2(char opponentChoice, char myChoice) {
    int points = 0;
    if (opponentChoice == 'A') {
        if      (myChoice == 'X') { return points = SCISSORS + LOSS; }
        else if (myChoice == 'Y') { return points = ROCK + DRAW;     }
        else if (myChoice == 'Z') { return points = PAPER + WIN;     }
        else    {std::cerr << "A: Invalid Value in column 2, exiting\n" << std::endl; exit(1);}
    }

    else if (opponentChoice == 'B') {
        if      (myChoice == 'X') { return points = ROCK + LOSS;     }
        else if (myChoice == 'Y') { return points = PAPER + DRAW;    }
        else if (myChoice == 'Z') { return points = SCISSORS + WIN;  }
        else    {std::cerr << "B: Invalid Value in column 2, exiting\n" << std::endl; exit(2);}
    }

    else if (opponentChoice == 'C') {
        if      (myChoice == 'X') { return points = PAPER + LOSS;    }
        else if (myChoice == 'Y') { return points = SCISSORS + DRAW; }
        else if (myChoice == 'Z') { return points = ROCK + WIN;      }
        else    {std::cerr << "C: Invalid Value in column 2, exiting\n" << std::endl; exit(3);}
    }
}


int calculatePart1(char opponentChoice, char myChoice) {
    int points = 0;
    if (opponentChoice == 'A') {
        if      (myChoice == 'X') { return points = ROCK + DRAW; }
        else if (myChoice == 'Y') { return points = PAPER + WIN; }
        else if (myChoice == 'Z') { return points = SCISSORS + LOSS;  }
        else    {std::cerr << "A: Invalid Value in column 2, exiting\n" << std::endl; exit(1);}
    }

    else if (opponentChoice == 'B') {
        if      (myChoice == 'X') { return points = ROCK + LOSS;  }
        else if (myChoice == 'Y') { return points = PAPER + DRAW; }
        else if (myChoice == 'Z') { return points = SCISSORS + WIN; }
        else    {std::cerr << "B: Invalid Value in column 2, exiting\n" << std::endl; exit(2);}
    }

    else if (opponentChoice == 'C') {
        if      (myChoice == 'X') { return points = ROCK + WIN; }
        else if (myChoice == 'Y') { return points = PAPER + LOSS;  }
        else if (myChoice == 'Z') { return points = SCISSORS + DRAW; }
        else    {std::cerr << "C: Invalid Value in column 2, exiting\n" << std::endl; exit(3);}
    }
}

int main() {
    std::fstream inputFile;
    inputFile.open("input.txt");
    if (!inputFile.is_open()) {
        std::cerr << "Input file not opened, exiting\n" << std::endl;
        exit(0);
    }

    std::string line;
    int pointsPart1 = 0, pointsPart2 = 0;
    while(std::getline(inputFile, line)) {
        pointsPart1 += calculatePart1(line.at(0), line.at(2));
        pointsPart2 += calculatePart2(line.at(0), line.at(2));
    }
    std::cout << "Part 1 points is: " << pointsPart1 << std::endl;
    std::cout << "Part 2 points is: " << pointsPart2 << std::endl;
    inputFile.close();
    return 0;
}
