#pragma once

#include <stdint.h>
#include <cstring>

namespace SixPackLib
{
    struct SixPackMessage {
        uint32_t type;
        uint8_t data[32];
        uint8_t size;
    };

    enum MessageType {
        CRITICAL        = 0x0010,
        ERROR           = 0x0020,
        WARNING         = 0x0030,
        ACTION          = 0x0100, // 0x0100 --> 0x0FFF
        EVENT           = 0x1000, // 0x1000 --> 0x19FF
        CONFIG_WRITE    = 0x1B00,
        CONFIG_READ     = 0x1D00,
        ALIVE           = 0x1F00,
        INFO            = 0x1F40,
        DEBUG           = 0x1F80,
        TRACE           = 0x1FF0
    };

    enum ActionType {
        FEEDBACKLED                 = MessageType::ACTION | 0x0200,
        FEEDBACKLED_BRIGHTNESS      = MessageType::ACTION | 0x0201,
        FEEDBACKLED_EFFECT          = MessageType::ACTION | 0x0202,
        FEEDBACKLED_GLOBAL_EFFECT   = MessageType::ACTION | 0x0203,
    };

    enum EventType {


    };

    class Message {
        public:
            static SixPackMessage Critical(uint16_t subType, uint8_t* message, uint8_t size);
            static SixPackMessage Error(uint16_t subType, uint8_t* message, uint8_t size);
            static SixPackMessage Warning(uint16_t subType, uint8_t* message, uint8_t size);
            static SixPackMessage Action(uint16_t subType, uint8_t* message, uint8_t size);
            static SixPackMessage Event(uint16_t subType, uint8_t* message, uint8_t size);
            static SixPackMessage ConfigWrite(uint16_t subType, uint8_t* message, uint8_t size);
            static SixPackMessage ConfigRead(uint16_t subType, uint8_t* message, uint8_t size);
            static SixPackMessage Alive(uint16_t subType, uint8_t* message, uint8_t size);
            static SixPackMessage Info(uint16_t subType, uint8_t* message, uint8_t size);
            static SixPackMessage Debug(uint16_t subType, uint8_t* message, uint8_t size);
            static SixPackMessage Trace(uint16_t subType, uint8_t* message, uint8_t size);

            
    };
} // namespace SixPackLib::Message


