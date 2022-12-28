#include "Message.h"

using namespace SixPackLib;

SixPackMessage Message::Critical(uint16_t subType, uint8_t* message, uint8_t size) {
    SixPackMessage msg = { (uint32_t) MessageType::CRITICAL | subType, { 0 }, size};
    std::memcpy(msg.data, message, size);
    return msg;
}

SixPackMessage Message::Error(uint16_t subType, uint8_t* message, uint8_t size) {
    SixPackMessage msg = { (uint32_t) MessageType::ERROR | subType, { 0 }, size};
    std::memcpy(msg.data, message, size);
    return msg;
}

SixPackMessage Message::Warning(uint16_t subType, uint8_t* message, uint8_t size) {
    SixPackMessage msg = { (uint32_t) MessageType::WARNING | subType, { 0 }, size};
    std::memcpy(msg.data, message, size);
    return msg;
}

SixPackMessage Message::Action(uint16_t subType, uint8_t* message, uint8_t size) {
    SixPackMessage msg = { (uint32_t) MessageType::ACTION | subType, { 0 }, size};
    std::memcpy(msg.data, message, size);
    return msg;
}

SixPackMessage Message::Event(uint16_t subType, uint8_t* message, uint8_t size) {
    SixPackMessage msg = { (uint32_t) MessageType::EVENT | subType, { 0 }, size};
    std::memcpy(msg.data, message, size);
    return msg;
}

SixPackMessage Message::ConfigWrite(uint16_t subType, uint8_t* message, uint8_t size) {
    SixPackMessage msg = { (uint32_t) MessageType::CONFIG_WRITE | subType, { 0 }, size};
    std::memcpy(msg.data, message, size);
    return msg;
}

SixPackMessage Message::ConfigRead(uint16_t subType, uint8_t* message, uint8_t size) {
    SixPackMessage msg = { (uint32_t) MessageType::CONFIG_READ | subType, { 0 }, size};
    std::memcpy(msg.data, message, size);
    return msg;
}

SixPackMessage Message::Alive(uint16_t subType, uint8_t* message, uint8_t size) {
    SixPackMessage msg = { (uint32_t) MessageType::ALIVE | subType, { 0 }, size };
    std::memcpy(msg.data, message, size);
    return msg;
}

SixPackMessage Message::Info(uint16_t subType, uint8_t* message, uint8_t size) {
    SixPackMessage msg = { (uint32_t) MessageType::INFO | subType, { 0 }, size};
    std::memcpy(msg.data, message, size);
    return msg;
}

SixPackMessage Message::Debug(uint16_t subType, uint8_t* message, uint8_t size) {
    SixPackMessage msg = { (uint32_t) MessageType::DEBUG | subType, { 0 }, size};
    std::memcpy(msg.data, message, size);
    return msg;
}

SixPackMessage Message::Trace(uint16_t subType, uint8_t* message, uint8_t size) {
    SixPackMessage msg = { (uint32_t) MessageType::TRACE | subType, { 0 }, size};
    std::memcpy(msg.data, message, size);
    return msg;
}