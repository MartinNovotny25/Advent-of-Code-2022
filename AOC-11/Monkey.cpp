//
// Created by novot on 02/06/2024.
//

#include "Monkey.h"
#include <cmath>

#include <bits/chrono.h>

void Monkey::doMonkeyBusiness(std::vector<Monkey>& monkeyVector) {
    int32_t& monkeyIfTrue = this->targetMonkeys.first;
    int32_t& monkeyIfFalse = this->targetMonkeys.second;

    if (this->items.empty()) {
        return;
    }
    // For every item, do the reuqired sequence
    for(auto itemIterator = this->items.begin(); itemIterator != this->items.end();) {

        this->inspectionCounter++;

        // Perform operation
        int32_t& currentItem = *itemIterator;

        //std::cout << "Current item: " << currentItem << std::endl;

        this->doOperation(currentItem);

        //std::cout << "After operation: " << currentItem << std::endl;

        // Divide value by 3
        //currentItem /= 3;
        currentItem = std::round(currentItem / 3);

        //std::cout << "After division: " << currentItem << std::endl;

        if (currentItem % this->divisor == 0) {

            //std::cout << "Item divisible by: " << this->divisor << ", thrown to: " << monkeyIfTrue << std::endl;
            //std::cout << "Before remove: " << items.size() << std::endl;
            monkeyVector[monkeyIfTrue].items.push_back(currentItem);
            itemIterator = this->items.erase(itemIterator);
            //std::cout << std::endl;
            //std::cout << "After remove: " << items.size() << std::endl;

        } else {

            //std::cout << "Item NOT divisible by: " << this->divisor  <<", thrown to: " << monkeyIfFalse << std::endl;
            //std::cout << "Before remove: " << items.size() << std::endl;
            monkeyVector[monkeyIfFalse].items.push_back(currentItem);
            itemIterator = this->items.erase(itemIterator);
            //std::cout << "After remove: " << items.size() << std::endl;
            //std::cout << std::endl;
        }

    }
}

void Monkey::doOperation(int32_t& item) {
    if (this->operation[3] == "*") {
        if(this->operation[4] == "old") {
            item *= item;
        } else {
            const int32_t constant = std::strtol(this->operation[4].c_str(), nullptr, 10);
            item *= constant;
        }

    } else if (this->operation[3] == "+") {
        if(this->operation[4] == "old") {
            item += item;
        } else {
            const int32_t constant = std::strtol(this->operation[4].c_str(), nullptr, 10);
            item += constant;
        }
    }
}
