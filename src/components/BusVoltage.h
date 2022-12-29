#pragma once

#include "Component.h"

class BusVoltage: public Component {
    public:
        BusVoltage(PinName adc_pin);
        void onRegister() override;
    private:
        AnalogIn busVoltage;
};