//
// Created by novot on 02/06/2024.
//

#ifndef MONKEY_H
#define MONKEY_H

#include <algorithm>
#include <cstdint>
#include <iostream>
#include <map>
#include <vector>

class Monkey {
public:
    int32_t                     index;
    int32_t                     inspectionCounter = 0;
    int32_t                     divisor;
    std::vector<int32_t>        items;
    std::vector<std::string>    operation;

    std::pair<int32_t, int32_t> targetMonkeys;

    void doMonkeyBusiness(std::vector<Monkey>& monkeyVector);
    void doOperation(int32_t& item);
};



#endif //MONKEY_H
