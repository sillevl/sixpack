#pragma once

#include "mbed.h"
#include "Stm32UniqueId.h"
#include "Messages/Message.h"
#include "Blik.h"

static const auto AliveInterval = 10s;
static const auto TPHInterval = 10s;

class SixPack {
    public:
        enum ButtonState {  RELEASED = 0, PRESSED = 1 };

        struct TPH {
            float temperature;
            float pressure;
            float humidity;
        };

        struct ButtonEvent {
            uint8_t index;
            ButtonState state;
            uint32_t time = 0;
        };

        struct FeedbackLedStatus {
            uint8_t index;
            uint8_t brightness;
        };

        SixPack(CAN* can);
        void send(SixPackLib::SixPackMessage);
        void onActivity(mbed::Callback<void()> cb);
        void setStatusLed(PinName pin, bool negativeLogic = false);
        void setDeviceType(uint16_t deviceType);
        void setFirmwareVersion(uint16_t firmwareVersion);
        void setTPHCallback(mbed::Callback<TPH()> callback);
        void setBusVoltageCallback(mbed::Callback<float()> callback);
        void feedbackLedsEvent(mbed::Callback<void(FeedbackLedStatus status)> callback);

        void buttonUpdate(ButtonEvent event);

    private:
        Blik blik;
        EventQueue queue;
        Thread eventThread;
        DigitalOut* statusLed;
        uint16_t deviceId = 0;
        uint16_t deviceType = 0;
        uint16_t firmwareVersion = 0;
        bool statusLedNegativeLogic = false;

        void parseMessage(BlikMessage message);
        void setDeviceId();
        void blinkStatusLed();
        void sendAliveMessage();
        void sendTPHMessage();
        void sendBusVoltageMessage();

        mbed::Callback<TPH()> tphCallback;
        mbed::Callback<float()> busVoltageCallback;
        mbed::Callback<void(FeedbackLedStatus)> updateFeedbackLedsCallback;
};
