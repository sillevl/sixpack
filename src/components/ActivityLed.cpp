#include "ActivityLed.h"

ActivityLed::ActivityLed(PinName status_led_pin, bool negative_logic) :
StatusLed(status_led_pin, negative_logic)
{
    off();
}

void ActivityLed::blink() {
    on();
    sixPack->queue.call_in(50ms, mbed::Callback<void()>(this, &ActivityLed::off));
}

void ActivityLed::onRegister() {
    on();
    sixPack->queue.call_in(200ms, mbed::Callback<void()>(this, &ActivityLed::off));
    sixPack->onActivity( [this] () {
        blink();
    });
}