//
// Created by novot on 02/06/2024.
//

#include "Monkey.h"
#include <cmath>

#include <bits/chrono.h>

std::vector<int64_t> findAllDivisors(uint64_t num);

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
        uint64_t& currentItem = *itemIterator;

        // This can be perfomed before hand, but I grew tired till I figured this out so it will stay like this
        uint64_t newDivisor = 1;
        for (const auto& monkey : monkeyVector) {
            newDivisor *= monkey.divisor;
        }

        this->doOperation(currentItem);
        currentItem %= newDivisor;

        if (currentItem % this->divisor == 0) {
            monkeyVector[monkeyIfTrue].items.push_back(currentItem);
            itemIterator = this->items.erase(itemIterator);

        } else {
            monkeyVector[monkeyIfFalse].items.push_back(currentItem);
            itemIterator = this->items.erase(itemIterator);
        }
    }
}

void Monkey::doOperation(uint64_t& item) {
    if (this->operation[3] == "*") {
        if(this->operation[4] == "old") {
            item *= item;
        } else {
            const int64_t constant = std::strtol(this->operation[4].c_str(), nullptr, 10);
            item *= constant;
        }

    } else if (this->operation[3] == "+") {
        if(this->operation[4] == "old") {
            item += item;
        } else {
            const int64_t constant = std::strtol(this->operation[4].c_str(), nullptr, 10);
            item += constant;
        }
    }
}

