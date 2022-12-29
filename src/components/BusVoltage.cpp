#include "BusVoltage.h"
#include "Events.h"

#define TRACE_GROUP "BusVoltage"

BusVoltage::BusVoltage(PinName adc_pin) : busVoltage(adc_pin)
{
    busVoltage.set_reference_voltage(3.3f);
}

void BusVoltage::onRegister() {
    sixPack->queue.call_every(5s, [this](){
        float voltage = busVoltage.read_voltage() * ((200.0f + 10.0f) / 10.0f) * 1.02f;  // calibration factor (tolerance)
        tr_info("Busvoltage: %.3f", voltage);
        sixPack->send( SixPackLib::Events::BusVoltage(voltage));
    });
}