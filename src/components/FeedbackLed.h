#pragma once

#include "Component.h"
#include "SixPack.h"

class FeedbackLed: public Component {
    public:
        FeedbackLed();
        void onRegister() override;
        void onMessage(mbed::Callback<void(uint8_t index, uint8_t brightness)> callback);
        void onSetBrightness(mbed::Callback<void(uint8_t brightness)> callback);
        void onEffect(mbed::Callback<void(uint8_t index, uint16_t effectType, uint32_t duration)> callback);
        void onGlobalEffect(mbed::Callback<void(uint16_t effectType, uint32_t duration)> callback);
    private:
         mbed::Callback<void(uint8_t index, uint8_t brightness)> onMessageHandler;
         mbed::Callback<void(uint8_t brightness)> onBrightnessHandler;
         mbed::Callback<void(uint8_t index, uint16_t effectType, uint32_t duration)> onEffectHandler;
         mbed::Callback<void(uint16_t effectType, uint32_t duration)> onGlobalEffectHandler;
};