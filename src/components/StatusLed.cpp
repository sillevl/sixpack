
#include "StatusLed.h"

StatusLed::StatusLed(PinName status_led_pin, bool negative_logic) :
status_led(status_led_pin)
{
    this->negative_logic = negative_logic;
}

void StatusLed::set(bool status) {
    status_led.write(negative_logic != status);
}

void StatusLed::on() {
    set(true);
}

void StatusLed::off() {
    set(false);
}