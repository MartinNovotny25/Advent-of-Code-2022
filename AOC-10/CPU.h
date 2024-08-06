//
// Created by novot on 01/06/2024.
//

#ifndef CPU_H
#define CPU_H

#include <string>
#include <cstdint>

#include "CRT.h"

struct operationStruct {
    std::string opCode;
    int64_t     opValue;
};

class CPU {
private:
    int64_t registerValue           = 1;
    int64_t currentTick             = 0;
    int64_t totalSignalStrength     = 0;
    int32_t nextSignalCheck         = 20;
    CRT     crt                         ;

public:
                    void    executeOperation(const operationStruct& operation);
                    void    increaseRegisterValue(int64_t value);
                    void    increaseTickCounter(int64_t value);
    [[nodiscard]]   int64_t getRegisterValue() const;
    [[nodiscard]]   int64_t getTickValue() const ;
    [[nodiscard]]   int64_t getTotalSignalStrength() const ;
};



#endif //CPU_H
