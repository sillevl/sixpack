#pragma once

#include "StatusLed.h"

class ActivityLed:  public StatusLed {
    public:
        ActivityLed(PinName status_led_pin, bool negative_logic = false);
        void blink();
        void onRegister() override;
};