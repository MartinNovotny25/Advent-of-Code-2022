// Advent of Code, Day 8
// Author: Martin Novotný Mlinárcsik, FIT BUT
// Github: https://github.com/MartinNovotny25
// LinkedIn: https://www.linkedin.com/in/martin-novotn%C3%BD-mlin%C3%A1rcsik-377616242/
// 28.5.2024

#include <iostream>
#include <cstdint>
#include <string>
#include <vector>
#include <chrono>

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


int main() {
    auto start = std::chrono::high_resolution_clock::now();
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
        if (symbol == '\n') { height++                          ;}
        else                { forestVector1D.push_back(symbol-48 )  ;}
        if (height == 0)    { width++                           ;}

        symbol = static_cast<char>(fgetc(inputFile));
    }

    std::cout << height << " " << width << std::endl;

    int32_t forestSize = width * height;
    int32_t visibleTrees = 0;

    // Start y from 1 since the first row is always visible
    // Start x from 1 since side is always visible, upper bound is width -1 since side is visible
    for (int16_t  y = 1; y < (height-1); ++y) {
        for (int16_t  x = 1; x < (width-1); ++x) {

            int32_t&     treeHeight     = forestVector1D[(y * width)  + x];

            uint8_t quadrant = calculateQuadrant(height,width,y,x);
            //std::cout << (int)quadrant << std::endl;
            bool visible = calculateVisibility(forestVector1D,y,x,height,width,treeHeight,quadrant);
            if (visible) {
                //std::cout << "POINT [" << y << ", " << x << "] VISIBLE" << std::endl;
                visibleTrees++;
            } else {
                //std::cout << "POINT [" << y << ", " << x << "] NOT VISIBLE" << std::endl;
            }
        }
    }

    for (auto val : forestVector1D) {
        //std::cout << val << " ";
    }

    std::cout << (visibleTrees + (2*height) + (2*(width-2)))<< std::endl;
    std::cout << visibleTrees << std::endl;
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop-start);
    std::cout << "Duration: " << duration.count() << std::endl;

    return 0;
}

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

    // if (quadrant == UP_RIGHT) {
         //std::cout << "CURRENT POINT: " << currentWidth << " " << currentHeight << std::endl;
         //std::cout << "VALUE: " << (int)treeHeight << std::endl;
        const int32_t currentPosition = (currentHeight * maxWidth) + currentWidth;
         //std::cout << "CURRENT POSITION: " << currentPosition << std::endl;


       // if (currentWidth > currentHeight) { // closer the side than top
            for (uint16_t i = 1; i < (maxWidth-currentWidth); ++i) {
                 // std::cout << "MOVE RIGHT: " <<  currentPosition + i << std::endl;
                 // std::cout << "VALUE: " << forestVector[currentPosition + i] << std::endl;
                if (treeHeight > forestVector[currentPosition + i]) {
                    // std::cout << "MOVE RIGHT: " <<  currentPosition + i << std::endl;
                    // std::cout << "VALUE: " << forestVector[currentPosition + i] << std::endl;
                    // return true;
                    rightHidden = false;
                } else {
                    rightHidden = true;
                    break;
                }
            }
       // } else {
            for (uint16_t i = 1; 0 <= (currentHeight-i); ++i) { // Move to the top
                 // std::cout << "MOVE UP: " <<  currentPosition - (maxWidth*i) << std::endl;
                 // std::cout << "VALUE: " << forestVector[currentPosition - (maxWidth*i)] << std::endl;
                if (treeHeight > forestVector[currentPosition - (maxWidth*i)]) {
                    // std::cout << "MOVE UP: " <<  currentPosition - (maxWidth*i) << std::endl;
                    // std::cout << "VALUE: " << forestVector[currentPosition - (maxWidth*i)] << std::endl;
                    upHidden = false;
                    // return true;
                } else {
                    upHidden = true;
                    break;
                }
            }

            for (uint16_t i = 1; i <= currentWidth; ++i) { // move to the left
                 // std::cout << "MOVE LEFT: " <<  currentPosition - i << std::endl;
                 // std::cout << "VALUE: " << forestVector[currentPosition - i] << std::endl;
                if (treeHeight > forestVector[currentPosition - i]) {
                    // std::cout << "MOVE LEFT: " <<  currentPosition - i << std::endl;
                    // std::cout << "VALUE: " << forestVector[currentPosition - i] << std::endl;
                    leftHidden = false;
                    //return true;
                } else {
                    leftHidden = true;
                    break;
                }
            }

            for (uint16_t i = 1; i < (maxHeight - currentHeight); ++i) { // Move to the bottom
                 // std::cout << "MOVE DOWN: " << currentPosition + (maxWidth*i) << std::endl;
                 // std::cout << "VALUE: " << forestVector[currentPosition + (maxWidth*i)] << std::endl;
                if (treeHeight > forestVector[currentPosition + (maxWidth*i)]) {
                    // std::cout << "MOVE DOWN: " << currentPosition + (maxWidth*i) << std::endl;
                    // std::cout << "VALUE: " << forestVector[currentPosition + (maxWidth*i)] << std::endl;
                    downHidden = false;
                    //return true;
                } else {
                    downHidden = true;
                    break;
                }
            }


        // }
   // }
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
        // std::cout << "MOVE LEFT: " <<  currentPosition - i << std::endl;
        // std::cout << "VALUE: " << forestVector[currentPosition - i] << std::endl;
        if (treeHeight > forestVector[currentPosition - i]) {
            // std::cout << "MOVE LEFT: " <<  currentPosition - i << std::endl;
            // std::cout << "VALUE: " << forestVector[currentPosition - i] << std::endl;
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

