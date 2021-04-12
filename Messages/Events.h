#pragma once

#include "Message.h"
#include <cstring>

using namespace SixPackLib;

class Events {
    private:
        enum SubType {
            BUTTON      = 0x0000,
            TPH_         = 0x0100
        };

    public:
        static SixPackMessage Button(uint8_t index, uint8_t state, uint32_t timeDelta);
        static SixPackMessage TPH(float temperature, float humidity, float pressure);
};