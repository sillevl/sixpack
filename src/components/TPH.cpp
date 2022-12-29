#include "TPH.h"
#include "Events.h"

#define TRACE_GROUP "TPH"

TPH::TPH(BME280* tph)
{
    this->tph = tph;
}

void TPH::onRegister() {
    sixPack->queue.call_every(5s, [this](){
        tr_info("TPH: %.2f°C %.2f%%, %f", tph->getTemperature(), tph->getHumidity(), tph->getPressure());
        sixPack->send(
            SixPackLib::Events::TPH(tph->getTemperature(), tph->getHumidity(), tph->getPressure())
        );
    });
}