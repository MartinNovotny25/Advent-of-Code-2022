//
// Created by novot on 01/06/2024.
//

#include "CPU.h"
#include <iostream>

int64_t CPU::getRegisterValue() const {
    return this->registerValue;
}

void CPU::executeOperation(const operationStruct &operation) {
    if (operation.opCode == "addx") {

        this->increaseTickCounter(1);
        if (this->getTickValue() == this->nextSignalCheck) {

            this->nextSignalCheck       += 40;
            this->totalSignalStrength   += this->getTickValue() * this->getRegisterValue();
        }

        this->crt.draw(getTickValue()-1);

        this->increaseTickCounter(1);
        if (this->getTickValue() == this->nextSignalCheck) {

            this->nextSignalCheck       += 40;
            this->totalSignalStrength   += this->getTickValue() * this->getRegisterValue();
        }

        this->crt.draw(getTickValue()-1);
        this->increaseRegisterValue(operation.opValue);
        this->crt.moveSprite(this->getRegisterValue());


    } else {

        this->increaseTickCounter(1);
        if (this->getTickValue() == this->nextSignalCheck) {
            this->nextSignalCheck       += 40;
            this->totalSignalStrength   += this->getTickValue() * this->getRegisterValue();
        }
        this->crt.draw(getTickValue()-1);

        if(getTickValue() == 240) {
            crt.printScreen();
        }
    }
}

void CPU::increaseRegisterValue(const int64_t value) {
    this->registerValue += value;
}

void CPU::increaseTickCounter(const int64_t value) {
    this->currentTick += value;
}

int64_t CPU::getTickValue() const {
    return this->currentTick;
}

int64_t CPU::getTotalSignalStrength() const {
    return this->totalSignalStrength;
}
