#pragma once

#include "Message.h"
#include <cstring>

using namespace SixPackLib;

class Alive {

    enum SubType {
        ALIVE      = 0x0000
    };

    public:
        static SixPackMessage DeviceInfo(uint16_t deviceType, uint32_t firmwareVersion, uint32_t uptime, uint16_t bootCount);
};