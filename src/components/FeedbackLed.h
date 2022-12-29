#pragma once

#include "Component.h"
#include "SixPack.h"

class FeedbackLed: public Component {
    public:
        FeedbackLed();
        void onRegister() override;
        void onMessage(mbed::Callback<void(uint8_t index, uint8_t brightness)> callback);
    private:
         mbed::Callback<void(uint8_t index, uint8_t brightness)> onMessageHandler;
};