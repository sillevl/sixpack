#include "SixPack.h"
#include "mbedtls/sha256.h" /* SHA-256 only */
#include "Blik.h"
#include <chrono>
#include "Messages/Alive.h"
#include "Messages/Events.h"
#include "mbed_trace.h"

#define TRACE_GROUP "SIXPACK"

using namespace SixPackLib;

SixPack::SixPack(events::EventQueue* ev_queue, uint32_t firmwareVersion):
    queue(32 * EVENTS_EVENT_SIZE),
    can(MBED_CONF_SIXPACK_CAN_TXD_PIN, MBED_CONF_SIXPACK_CAN_RXD_PIN, MBED_CONF_SIXPACK_CAN_BITRATE),
    blik(&can, ev_queue)
{
    queue.chain(ev_queue);
    tr_info("*** Start SixPack ***");
    setDeviceType(spha::MBED_CONF_SIXPACK_DEVICE_TYPE);
    setFirmwareVersion(firmwareVersion);
    setDeviceId();
    blik.onMessage([this](BlikMessage message) {
        // this->blinkStatusLed();
        parseMessage(message);
        // std::list<Component *>::iterator iterator = components.begin();
        // while (iterator != components.end()) {
        //     (*iterator)->onMessage(message);
        //     ++iterator;
        // }

        // std::for_each(std::begin(components), std::end(components), [message](IComponent* component) {
        //     // std::cout << value << "\n";
        //     (*component)->onMessage(message);
        // });
        if(activityCallback) { activityCallback(); }
    });

    // TODO: random startup delay (use unique_id for seed)
    queue.call_every(AliveInterval, this, &SixPack::sendAliveMessage);
    sendAliveMessage();  
}

void SixPack::registerComponent(Component* component) {
    component->setSixPack(this);
    component->onRegister();
    components.push_back(component);
}

void SixPack::unregisterComponent(Component* component) {
    components.remove(component);
    // TODO
}

void SixPack::send(SixPackMessage message){
    uint32_t canId = message.type << 16 | deviceId;
    blik.send(canId, message.data, message.size);
    // blinkStatusLed();
    if(activityCallback) { activityCallback(); }
}

void SixPack::setDeviceId(){
    // get STM32 Unique ID
    uint8_t uid[12] = { 0 };
    uint8_t* uid_reg = Stm32UniqueId::getId();
    std::copy(uid_reg, uid_reg + 12, uid);

    // Use SMT32 Unique ID to generate a hash
    unsigned char hash[32]; /* SHA-256 outputs 32 bytes */
    mbedtls_sha256( (const unsigned char*) uid, 12, hash, 0);

    std::memcpy( &deviceId, hash, 2);

    tr_info("Device id: %04X\r\n", deviceId);
}

void SixPack::setDeviceType(uint16_t deviceType) {
    this->deviceType = deviceType;
}

void SixPack::setFirmwareVersion(uint16_t firmwareVersion) {
    this->firmwareVersion = firmwareVersion;
}

void SixPack::onActivity(mbed::Callback<void()> cb) {
    activityCallback = cb;
}

void SixPack::onMessage( uint32_t type , mbed::Callback<void(SixPackLib::SixPackMessage)> cb) {
    onMessageMap.insert({type, cb});
    // messageCallback = cb;
}

void SixPack::sendAliveMessage() {
    // TODO: implement bootcounter
    auto now_ms = std::chrono::time_point_cast<std::chrono::seconds>(Kernel::Clock::now());
    long uptime = now_ms.time_since_epoch().count();
    send( Alive::DeviceInfo(deviceType, firmwareVersion, uptime, 0) );
}

void SixPack::parseMessage(BlikMessage message) {
    uint16_t id = message.type & 0xFFFF;
    uint16_t type = message.type >> 16;

    // TODO: add filters dynamically with callbacks defined in lib/ files

    tr_debug("Blikmessage: (%X, %d)", message.type, message.size);
    tr_debug("%s", tr_array(message.data, message.size));

    if(id == deviceId) {
        auto find = onMessageMap.find(type);
        if (find != onMessageMap.end()) {
        // if(messageCallback) {
            SixPackLib::SixPackMessage msg;
            msg.type = type;
            msg.size = message.size;
            memcpy(msg.data, message.data, message.size);
            find->second(msg);
        }
        // if(type == 0x0110) { // Set relay
        //     RelayUpdateStatus status { message.data[0], message.data[1] };
        //     updateRelayCallback(status);
        // }
    }
}