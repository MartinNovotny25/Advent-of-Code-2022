// Advent of Code, Day 8
// Author: Martin Novotný Mlinárcsik, FIT BUT
// Github: https://github.com/MartinNovotny25
// LinkedIn: https://www.linkedin.com/in/martin-novotn%C3%BD-mlin%C3%A1rcsik-377616242/
// 28.5.2024

#include <iostream>
#include <cstdint>
#include <string>
#include <vector>

#define UP_RIGHT    0
#define DOWN_RIGHT  1
#define DOWN_LEFT   2
#define UP_LEFT     3

uint8_t calculateQuadrant(
            const uint16_t          maxHeight,
            const uint16_t          maxWidth,
            const uint16_t          currentHeight,
            const uint16_t          currentWidth);

bool calculateVisibility(
        const std::vector<int32_t>&  forestVector,
        const int16_t&             currentHeight,
        const int16_t&             currentWidth,
        const int16_t&             maxHeight,
        const int16_t&             maxWidth,
        const int32_t&               treeHeight,
        const uint8_t&              quadrant);

bool checkUp( const std::vector<int32_t>& forestVector,
                const int16_t&              currentHeight,
                const int16_t&              currentWidth,
                const int16_t&              maxHeight,
                const int16_t&              maxWidth,
                const int32_t&              treeHeight);

bool checkDown( const std::vector<int32_t>& forestVector,
                const int16_t&              currentHeight,
                const int16_t&              currentWidth,
                const int16_t&              maxHeight,
                const int16_t&              maxWidth,
                const int32_t&              treeHeight);

bool checkLeft( const std::vector<int32_t>& forestVector,
                const int16_t&              currentHeight,
                const int16_t&              currentWidth,
                const int16_t&              maxHeight,
                const int16_t&              maxWidth,
                const int32_t&              treeHeight);

bool checkRight( const std::vector<int32_t>& forestVector,
                const int16_t&              currentHeight,
                const int16_t&              currentWidth,
                const int16_t&              maxHeight,
                const int16_t&              maxWidth,
                const int32_t&              treeHeight);

int main() {
    // Input file variable and path
    FILE* inputFile;
    inputFile = fopen("C:\\Projects\\Advent-of-Code-2022\\AOC-8\\input.txt","r");

    // If file not opened, exit
    if (inputFile == nullptr) {
        std::cerr << "Input file not opened" << std::endl;
        exit(1);
    }

    // Forest vector definition
    std::vector<int32_t> forestVector1D;

    // Variables for input reading and input dimensions
    char                        symbol = static_cast<char>(fgetc(inputFile));
    int16_t                     width = 0;
    int16_t                     height = 0;

    // Fill 1D forest vector and determine dimensions
    while (symbol != EOF) {
        if (symbol == '\n') { height++                                  ;}
        else                { forestVector1D.push_back(symbol-48 )    ;}
        if (height == 0)    { width++                                   ;}

        symbol = static_cast<char>(fgetc(inputFile));
    }

    int32_t visibleTrees = 0;

    // Start y from 1 since the first row is always visible
    // Start x from 1 since side is always visible, upper bound is width -1 since side is visible
    for (int16_t  y = 1; y < (height-1); ++y) {
        for (int16_t  x = 1; x < (width-1); ++x) {

            int32_t&    treeHeight      = forestVector1D[(y * width)  + x];
            uint8_t     quadrant        = calculateQuadrant(height,width,y,x);
            bool        visible         = calculateVisibility(forestVector1D,y,x,height,
                                        width,treeHeight,quadrant);

            if (visible) { visibleTrees++; }
        }
    }

    std::cout << (visibleTrees + (2*height) + (2*(width-2)))<< std::endl;
    return 0;
}

// Determine the quadrant in which the tree is situated
uint8_t calculateQuadrant(
            const uint16_t          maxHeight,
            const uint16_t          maxWidth,
            const uint16_t          currentHeight,
            const uint16_t          currentWidth)
{

    if (currentWidth > maxWidth / 2) {
        return (currentHeight > maxHeight / 2) ? DOWN_RIGHT : UP_RIGHT;
    } else {
        return (currentHeight > maxHeight / 2) ? DOWN_LEFT : UP_LEFT;
    }
}


// Function for calclating overall visibility from all directions
// Depending on the quadrant in which the tree is situated, different directions are being checked first.
// We check the direction which is closes the edge first and if the tree is visible from that side, we don't need
// to traverse the longer directions, saving time

bool calculateVisibility(
        const std::vector<int32_t>& forestVector,
        const int16_t&              currentHeight,
        const int16_t&              currentWidth,
        const int16_t&              maxHeight,
        const int16_t&              maxWidth,
        const int32_t&              treeHeight,
        const uint8_t&              quadrant)
{
    bool        leftHidden     = true;
    bool        rightHidden    = true;
    bool        upHidden       = true;
    bool        downHidden     = true;

    if (quadrant == UP_RIGHT) {
        if ((maxHeight - currentHeight) > (maxWidth-currentWidth)) {
            rightHidden = checkRight(forestVector, currentHeight, currentWidth, maxHeight, maxWidth, treeHeight);
            upHidden    = checkUp(forestVector, currentHeight, currentWidth, maxHeight, maxWidth, treeHeight);
            downHidden  = checkDown(forestVector, currentHeight, currentWidth, maxHeight, maxWidth, treeHeight);
            leftHidden  = checkLeft(forestVector, currentHeight, currentWidth, maxHeight, maxWidth, treeHeight);
        } else {
            upHidden    = checkUp(forestVector, currentHeight, currentWidth, maxHeight, maxWidth, treeHeight);
            rightHidden = checkRight(forestVector, currentHeight, currentWidth, maxHeight, maxWidth, treeHeight);
            downHidden  = checkDown(forestVector, currentHeight, currentWidth, maxHeight, maxWidth, treeHeight);
            leftHidden  = checkLeft(forestVector, currentHeight, currentWidth, maxHeight, maxWidth, treeHeight);
        }
    } else if (quadrant == DOWN_RIGHT) {
        if ((maxHeight - currentHeight) > (maxWidth-currentWidth)) {
            rightHidden = checkRight(forestVector, currentHeight, currentWidth, maxHeight, maxWidth, treeHeight);
            downHidden  = checkDown(forestVector, currentHeight, currentWidth, maxHeight, maxWidth, treeHeight);
            upHidden    = checkUp(forestVector, currentHeight, currentWidth, maxHeight, maxWidth, treeHeight);
            leftHidden  = checkLeft(forestVector, currentHeight, currentWidth, maxHeight, maxWidth, treeHeight);
        } else {
            downHidden  = checkDown(forestVector, currentHeight, currentWidth, maxHeight, maxWidth, treeHeight);
            rightHidden = checkRight(forestVector, currentHeight, currentWidth, maxHeight, maxWidth, treeHeight);
            upHidden    = checkUp(forestVector, currentHeight, currentWidth, maxHeight, maxWidth, treeHeight);
            leftHidden  = checkLeft(forestVector, currentHeight, currentWidth, maxHeight, maxWidth, treeHeight);
        }
    } else if (quadrant == DOWN_LEFT) {
        if ((maxHeight - currentHeight) > (maxWidth-currentWidth)) {
            leftHidden  = checkLeft(forestVector, currentHeight, currentWidth, maxHeight, maxWidth, treeHeight);
            downHidden  = checkDown(forestVector, currentHeight, currentWidth, maxHeight, maxWidth, treeHeight);
            rightHidden = checkRight(forestVector, currentHeight, currentWidth, maxHeight, maxWidth, treeHeight);
            upHidden    = checkUp(forestVector, currentHeight, currentWidth, maxHeight, maxWidth, treeHeight);
        } else {
            downHidden  = checkDown(forestVector, currentHeight, currentWidth, maxHeight, maxWidth, treeHeight);
            leftHidden  = checkLeft(forestVector, currentHeight, currentWidth, maxHeight, maxWidth, treeHeight);
            rightHidden = checkRight(forestVector, currentHeight, currentWidth, maxHeight, maxWidth, treeHeight);
            upHidden    = checkUp(forestVector, currentHeight, currentWidth, maxHeight, maxWidth, treeHeight);
        }
    } else if (quadrant == UP_LEFT) {
        if ((maxHeight - currentHeight) > (maxWidth-currentWidth)) {
            leftHidden  = checkLeft(forestVector, currentHeight, currentWidth, maxHeight, maxWidth, treeHeight);
            upHidden    = checkUp(forestVector, currentHeight, currentWidth, maxHeight, maxWidth, treeHeight);
            downHidden  = checkDown(forestVector, currentHeight, currentWidth, maxHeight, maxWidth, treeHeight);
            rightHidden = checkRight(forestVector, currentHeight, currentWidth, maxHeight, maxWidth, treeHeight);
        } else {
            upHidden    = checkUp(forestVector, currentHeight, currentWidth, maxHeight, maxWidth, treeHeight);
            leftHidden  = checkLeft(forestVector, currentHeight, currentWidth, maxHeight, maxWidth, treeHeight);
            downHidden  = checkDown(forestVector, currentHeight, currentWidth, maxHeight, maxWidth, treeHeight);
            rightHidden = checkRight(forestVector, currentHeight, currentWidth, maxHeight, maxWidth, treeHeight);
        }
    }

    // Tree is visible if it is visible from atleast 1 direction
    if (!upHidden || !downHidden || !rightHidden || !leftHidden) {
        return true;
    } else {
        return false;
    }
}

bool checkRight( const std::vector<int32_t>& forestVector,
                const int16_t&              currentHeight,
                const int16_t&              currentWidth,
                const int16_t&              maxHeight,
                const int16_t&              maxWidth,
                const int32_t&              treeHeight)
{
    bool rightHidden = true;
    const int32_t currentPosition = (currentHeight * maxWidth) + currentWidth;
    for (uint16_t i = 1; i < (maxWidth-currentWidth); ++i) {
        if (treeHeight > forestVector[currentPosition + i]) {
            rightHidden = false;
        } else {
            rightHidden = true;
            break;
        }
    }
    return rightHidden;
}

bool checkLeft( const std::vector<int32_t>& forestVector,
                const int16_t&              currentHeight,
                const int16_t&              currentWidth,
                const int16_t&              maxHeight,
                const int16_t&              maxWidth,
                const int32_t&              treeHeight)
{
    bool leftHidden = true;
    const int32_t currentPosition = (currentHeight * maxWidth) + currentWidth;
    for (uint16_t i = 1; i <= currentWidth; ++i) { // move to the left
        if (treeHeight > forestVector[currentPosition - i]) {
            leftHidden = false;
        } else {
            leftHidden = true;
            break;
        }
    }
    return leftHidden;
}

bool checkUp(   const std::vector<int32_t>& forestVector,
                const int16_t&              currentHeight,
                const int16_t&              currentWidth,
                const int16_t&              maxHeight,
                const int16_t&              maxWidth,
                const int32_t&              treeHeight)
{
    bool upHidden = true;
    const int32_t currentPosition = (currentHeight * maxWidth) + currentWidth;
    for (uint16_t i = 1; 0 <= (currentHeight-i); ++i) { // Move to the top
        if (treeHeight > forestVector[currentPosition - (maxWidth*i)]) {
            upHidden = false;
        } else {
            upHidden = true;
            break;
        }
    }
    return upHidden;
}

bool checkDown( const std::vector<int32_t>& forestVector,
                const int16_t&              currentHeight,
                const int16_t&              currentWidth,
                const int16_t&              maxHeight,
                const int16_t&              maxWidth,
                const int32_t&              treeHeight)
{
    bool downHidden = true;
    const int32_t currentPosition = (currentHeight * maxWidth) + currentWidth;
    for (uint16_t i = 1; i < (maxHeight - currentHeight); ++i) { // Move to the bottom
        if (treeHeight > forestVector[currentPosition + (maxWidth*i)]) {
            downHidden = false;
        } else {
            downHidden = true;
            break;
        }
    }
    return downHidden;
}

