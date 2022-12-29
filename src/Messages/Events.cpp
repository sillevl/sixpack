#include "Events.h"

using namespace SixPackLib;

SixPackMessage Events::TPH(float temperature,  float humidity, float pressure) {
    const uint8_t SIZE = 6;
    uint8_t message[SIZE] = { 0 };

    uint16_t temperature_fixed = temperature * 100;
    uint16_t humidity_fixed = humidity * 100;
    uint16_t pressure_fixed = pressure * 10;

    std::memcpy( message + 0, (void*) &temperature_fixed, 2);
    std::memcpy( message + 2, (void*) &humidity_fixed, 2);
    std::memcpy( message + 4, (void*) &pressure_fixed, 2);

    return Message::Event( (uint16_t) Events::SubType::TPH_, message, SIZE);
}

SixPackMessage Events::Button(uint8_t index, uint8_t state, uint32_t timeDelta) {
    const uint8_t SIZE = 6;
    uint8_t message[SIZE] = { 0 };

    message[0] = index;
    message[1] = state;
    std::memcpy( message + 2, (void*) &timeDelta, sizeof(timeDelta));

    return Message::Event( (uint16_t) Events::SubType::BUTTON, message, SIZE);
}

SixPackMessage Events::RelayUpdate(uint8_t index, uint8_t state) {
    const uint8_t SIZE = 2;
    uint8_t message[SIZE] = { 0 };

    message[0] = index;
    message[1] = state;

    return Message::Event( (uint16_t) Events::SubType::RELAY_UPDATE, message, SIZE);
}

SixPackMessage Events::BusVoltage(float voltage) {
    const uint8_t SIZE = 4;
    uint8_t message[SIZE] = { 0 };

    uint32_t millivolts = voltage * 1000.0f;
    memcpy(&message, &millivolts, sizeof(millivolts));

    return Message::Event( (uint16_t) Events::SubType::BUSVOLTAGE, message, SIZE);
}

