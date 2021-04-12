#pragma once

#include <stdint.h>

class Stm32UniqueId {
    public:
        static uint8_t* getId();
};