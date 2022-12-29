#include "FeedbackLed.h"
#include "Message.h"

#define TRACE_GROUP "FeedbackLed"

using namespace SixPackLib;

FeedbackLed::FeedbackLed()
{

}

void FeedbackLed::onRegister() {
    sixPack->onMessage( ActionType::FEEDBACKLED, [this] (SixPackMessage message){
        uint8_t index = message.data[0];
        uint8_t brightness = message.data[1];

        uint8_t gamma_lookup[] = { 0, 1, 2, 5, 10, 16, 25, 36, 50, 68, 89, 114, 142, 175, 213, 255 };
        brightness = gamma_lookup[brightness >> 4];

        if( onMessageHandler ) { 
            onMessageHandler(index, brightness);
        }
    });
}

void FeedbackLed::onMessage(mbed::Callback<void(uint8_t index, uint8_t brightness)> callback) {
    onMessageHandler = callback;
}