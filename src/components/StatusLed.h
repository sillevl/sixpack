#pragma once

#include "Component.h"

class StatusLed: public Component {
    public:
        StatusLed(PinName status_led_pin, bool negative_logic = false);
        void set(bool status);
        void on();
        void off();
    private:
        DigitalOut status_led;
        bool negative_logic;
};