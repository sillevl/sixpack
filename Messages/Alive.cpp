#include "Alive.h"
#include <cstdio>

SixPackMessage Alive::DeviceInfo(uint16_t deviceType, uint16_t firmwareVersion, uint32_t uptime, uint16_t bootCount) {
    const uint8_t SIZE = 10;
    uint8_t message[SIZE] = { 0 };

    std::memcpy(message + 0, (void*) &deviceType, sizeof(deviceType));
    std::memcpy(message + 2, (void*) &firmwareVersion, sizeof(firmwareVersion));
    std::memcpy(message + 4, (void*) &uptime, sizeof(uptime));
    std::memcpy(message + 8, (void*) &bootCount, sizeof(bootCount));

    return Message::Alive( (uint16_t) Alive::SubType::ALIVE, message, SIZE);
}