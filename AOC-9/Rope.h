//
// Created by novot on 30/05/2024.
//

#ifndef ROPE_H
#define ROPE_H

#include <cstdint>
#include <utility>
#include <vector>
#include <iostream>


class Rope {
public:
    explicit Rope(const std::pair<int32_t, int32_t>& position);

    std::pair<int32_t, int32_t> currentPosition;
    void move(const char* moveDirection);
};

class Head : public Rope {
public:
    explicit Head(const std::pair<int32_t, int32_t>& position) : Rope(position){};
};

class Tail : public Rope {
public:
    explicit Tail(const std::pair<int32_t, int32_t>& position) : Rope(position){};
    void     chaseHead(const Rope& headObj);
    void     checkIfVisited();
    bool     isTouchingHead(int32_t deltaX, int32_t deltaY);

    std::vector<std::pair<int32_t, int32_t>> visitedVector;
};


#endif //ROPE_H
