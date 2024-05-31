//
// Created by novot on 30/05/2024.
//

#include "Rope.h"

// Constructor
Rope::Rope(const std::pair<int32_t, int32_t>& position) {
    this->currentPosition = position;
}

// Simulates rope movement
void Rope::move(const char* moveDirection) {
    // Create references to pair members for readability
    int32_t& x = this->currentPosition.first;
    int32_t& y = this->currentPosition.second;

    switch (*moveDirection) {
        case 'U':
            y += 1;
            break;
        case 'D':
            y -= 1;
            break;
        case 'R':
            x += 1;
            break;
        case 'L':
            x -= 1;
            break;
        default:
            std::cerr << "Invalid move direction" << std::endl;
            exit(2);
    }
}

void Tail::chaseHead(const Rope& headObj) {

    // Make references to Head position for readability
    const int32_t& xHead = headObj.currentPosition.first;
    const int32_t& yHead = headObj.currentPosition.second;

    int32_t& xTail = this->currentPosition.first;
    int32_t& yTail = this->currentPosition.second;

    // Calculate differences between x and y coordinates of
    // Head and Tail
    const int32_t deltaX = abs(xHead - xTail);
    const int32_t deltaY = abs(yHead - yTail);

    // If Head and Tail are touching, Tail does not move
    if (this->isTouchingHead(deltaX, deltaY)) {
        return;
    }

    // If difference between x coordinates is larger than between y coordinates,
    // we move up/down, else left/right
    if (deltaX > deltaY) {
        if (xHead > xTail) {
            xTail = xHead - 1;
            yTail = yHead;
        } else {
            xTail = xHead + 1;
            yTail = yHead;
        }
    } else if (deltaX < deltaY) {
        if (yHead > yTail) {
            xTail = xHead;
            yTail = yHead - 1;
        } else {
            xTail = xHead;
            yTail = yHead + 1;
        }
    // If the differences are both 1, move diagonally based on where the head is
    } else {
        if (yHead > yTail) {
            if (xHead > xTail) {
                xTail = xHead - 1;
                yTail = yHead - 1;
            } else {
                xTail = xHead + 1;
                yTail = yHead - 1;
            }
        } else {
            if (xHead > xTail) {
                xTail = xHead - 1;
                yTail = yHead + 1;
            } else {
                xTail = xHead + 1;
                yTail = yHead + 1;
            }
        }
    }
}

// Check if the current position is in the visited vector.
void Tail::checkIfVisited() {
    for (const auto item : this->visitedVector) {
        if (item == this->currentPosition) {
            return;
        }
    }

    visitedVector.push_back(currentPosition);
}

// If the differences between x and y coordinates of Head and Tail are larger than 1,
// they can't be touching
bool Tail::isTouchingHead(const int32_t deltaX, const int32_t deltaY) {
    if (deltaX <= 1 && deltaY <= 1) {
        return true;
    } else {
        return false;
    }
}


