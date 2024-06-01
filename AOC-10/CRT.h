//
// Created by novot on 01/06/2024.
//

#ifndef CRT_H
#define CRT_H

#include <vector>
#include <iostream>
#include <cstdint>

struct sprite {
    int32_t left    = 0;
    int32_t middle  = 1;
    int32_t right   = 2;
};

class CRT {
public:
    explicit            CRT();
    void printScreen();
    void draw(int64_t CPUtick);
    void moveSprite(int32_t middlePosition);

private:
    std::vector<char>   screenVector;
    sprite              sprite;
};





#endif //CRT_H
