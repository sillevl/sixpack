#include "SixPack.h"
#include "mbedtls/sha256.h" /* SHA-256 only */
#include "Blik.h"
#include <chrono>
#include "Messages/Alive.h"
#include "Messages/Events.h"
#include "mbed_trace.h"

#define TRACE_GROUP "SIXPACK"

using namespace SixPackLib;

SixPack::SixPack(CAN* can, events::EventQueue* ev_queue) : blik(can), queue(32 * EVENTS_EVENT_SIZE), eventThread(osPriorityHigh) {
    queue.chain(ev_queue);
    tr_info("*** Start SixPack ***");
    setDeviceId();
    eventThread.start(callback(&queue, &EventQueue::dispatch_forever));
    blik.onMessage([this](BlikMessage message) {
        this->blinkStatusLed();
        parseMessage(message);
        std::list<IComponent *>::iterator iterator = components.begin();
        while (iterator != components.end()) {
            (*iterator)->onMessage(message);
            ++iterator;
        }

        // std::for_each(std::begin(components), std::end(components), [message](IComponent* component) {
        //     // std::cout << value << "\n";
        //     (*component)->onMessage(message);
        // });
    });

    // TODO: random startup delay (use unique_id for seed)
    queue.call_every(AliveInterval, this, &SixPack::sendAliveMessage);
    sendAliveMessage();  
}

void SixPack::registerComponent(IComponent* component) {
    components.push_back(component);
}

void SixPack::unregisterComponent(IComponent* component) {
    components.remove(component);
    // TODO
}

void SixPack::send(SixPackMessage message){
    uint32_t canId = message.type << 16 | deviceId;
    blik.send(canId, message.data, message.size);
    blinkStatusLed();
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

void SixPack::setStatusLed(PinName pin, bool negativeLogic) {
    statusLed = new DigitalOut(pin);
    statusLed->write(negativeLogic ? 0 : 1);
    this->statusLedNegativeLogic = negativeLogic;
}

void SixPack::blinkStatusLed() {
    if(!statusLed || !statusLed->is_connected()) { return; }
    int on = statusLedNegativeLogic ? 1 : 0;
    if( statusLed->read() == on) { return; }
    statusLed->write(on);
    queue.call_in(50ms, [this]() {
        int off = this->statusLedNegativeLogic ? 0 : 1;
        statusLed->write(off);
    });
}

void SixPack::sendAliveMessage() {
    // TODO: implement bootcounter
    auto now_ms = std::chrono::time_point_cast<std::chrono::seconds>(Kernel::Clock::now());
    long uptime = now_ms.time_since_epoch().count();
    send( Alive::DeviceInfo(deviceType, firmwareVersion, uptime, 0) );
}

// void SixPack::setTPHCallback(mbed::Callback<TPH()> callback) {
//     tphCallback = callback;
//     queue.call_every(TPHInterval, this, &SixPack::sendTPHMessage);
// }

// void SixPack::sendTPHMessage() {
//     TPH tph = tphCallback();
//     send( Events::TPH( tph.temperature, tph.humidity, tph.pressure ) );
// }

// void SixPack::setBusVoltageCallback(mbed::Callback<float()> callback) {
//     busVoltageCallback = callback;
//     queue.call_every(TPHInterval, this, &SixPack::sendBusVoltageMessage);
// }

// void SixPack::sendBusVoltageMessage() {
//     float voltage = busVoltageCallback();
//     // TODO: do something with the busvoltage
// }

// void SixPack::buttonUpdate(ButtonEvent event) {
//     send( Events::Button(event.index, event.state, event.time) );
// }

// void SixPack::feedbackLedsEvent(mbed::Callback<void(FeedbackLedStatus)> callback) {
//     updateFeedbackLedsCallback = callback;
// }
void SixPack::relayUpdateEvent(mbed::Callback<void(RelayUpdateStatus)> callback) {
    updateRelayCallback = callback;
}

void SixPack::parseMessage(BlikMessage message) {
    uint16_t id = message.type & 0xFFFF;
    uint16_t type = message.type >> 16;

    // TODO: add filters dynamically with callbacks defined in lib/ files

    // printf("----- message ---------\r\n");
    // printf("  type: %X\r\n", int(message.type));
    // for(int i = 0; i < message.size; i++) {
    //     printf("%X ", message.data[i]);
    // }
    // printf("\r\n");

    if(id == deviceId) {
        if(type == 0x0110) { // Set relay
            RelayUpdateStatus status { message.data[0], message.data[1] };
            updateRelayCallback(status);
        }
    //     if(type == 0x0200) { // Set status leds 
    //         FeedbackLedStatus status = { message.data[0], message.data[1] };
    //         updateFeedbackLedsCallback(status);
    //     }
    }
}