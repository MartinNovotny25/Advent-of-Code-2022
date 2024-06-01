//
// Created by novot on 01/06/2024.
//

#include "CRT.h"

#define SCREEN_SIZE 240

CRT::CRT() {
    this->screenVector.resize(SCREEN_SIZE, '.');
}

void CRT::draw(const int64_t CPUtick) {

    const int32_t offset = CPUtick / 40;
    if (CPUtick == this->sprite.left + (40 * offset)   ||
        CPUtick == this->sprite.middle + (40 * offset) ||
        CPUtick == this->sprite.right + (40 * offset)) {
            this->screenVector[CPUtick] = '#';
    }
}

void CRT::moveSprite(const int32_t middlePosition) {
    this->sprite.left   = middlePosition - 1;
    this->sprite.middle = middlePosition    ;
    this->sprite.right  = middlePosition + 1;
}

void CRT::printScreen() {
    for (int i = 0; i < 240; ++i) {
        std::cout << this->screenVector[i];
        if ((i+1) % 40 == 0) {
            std::cout << std::endl;
        }
    }
}
