#include "FeedbackLed.h"
#include "Message.h"

#define TRACE_GROUP "FeedbackLed"

using namespace SixPackLib;

FeedbackLed::FeedbackLed()
{

}

void FeedbackLed::onRegister() {
    // Set brightness of individual leds
    sixPack->onMessage( ActionType::FEEDBACKLED, [this] (SixPackMessage message){
        uint8_t index = message.data[0];
        uint8_t brightness = message.data[1];

        uint8_t gamma_lookup[] = { 0, 1, 2, 5, 10, 16, 25, 36, 50, 68, 89, 114, 142, 175, 213, 255 };
        brightness = gamma_lookup[brightness >> 4];

        if( onMessageHandler ) { 
            onMessageHandler(index, brightness);
        }
    });

    // Set global brightness of all leds
    sixPack->onMessage(ActionType::FEEDBACKLED_BRIGHTNESS, [this] (SixPackMessage message){
        uint8_t brightness = message.data[0];

        if( onBrightnessHandler ) { 
            onBrightnessHandler(brightness);
        }
    });

    // Play an effect on a single led for a given duration
    sixPack->onMessage(ActionType::FEEDBACKLED_EFFECT, [this] (SixPackMessage message){
        uint8_t index         = message.data[0];
        uint16_t effect_type  = message.data[1];
        uint32_t duration     = message.data[3];

        if( onEffectHandler ) { 
            onEffectHandler(index, effect_type, duration);
        }
    });

    // Play an effect on all leds for a given duration
    sixPack->onMessage(ActionType::FEEDBACKLED_GLOBAL_EFFECT, [this] (SixPackMessage message){
        uint16_t effect_type  = message.data[0];
        uint32_t duration     = message.data[2];

        if( onGlobalEffectHandler ) { 
            onGlobalEffectHandler(effect_type, duration);
        }
    });
}

void FeedbackLed::onMessage(mbed::Callback<void(uint8_t index, uint8_t brightness)> callback) {
    onMessageHandler = callback;
}

void FeedbackLed::onSetBrightness(mbed::Callback<void(uint8_t brightness)> callback) {
    onBrightnessHandler = callback;
}

void FeedbackLed::onEffect(mbed::Callback<void(uint8_t index, uint16_t effect_type, uint32_t duration)> callback) {
    onEffectHandler = callback;
}

void FeedbackLed::onGlobalEffect(mbed::Callback<void(uint16_t effect_type, uint32_t duration)> callback) {
    onGlobalEffectHandler = callback;
}