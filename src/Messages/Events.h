#pragma once

#include "Message.h"
#include <cstring>

namespace SixPackLib {
    class Events {
        private:
            enum SubType {
                BUTTON       = 0x0000,
                RELAY_UPDATE = 0x0020,
                TPH_         = 0x0100,
                BUSVOLTAGE   = 0x0110
            };

        public:
            static SixPackLib::SixPackMessage Button(uint8_t index, uint8_t state, uint32_t timeDelta);
            static SixPackLib::SixPackMessage TPH(float temperature, float humidity, float pressure);
            static SixPackLib::SixPackMessage RelayUpdate(uint8_t index, uint8_t state);
            static SixPackLib::SixPackMessage BusVoltage(float voltage);
    };
};