#include "TPH.h"
#include "Events.h"

void TPH::setTPHHandler(Callback<TPHData()> handler) {
    onTPHHandler = handler;
    sixPack->queue.call_every(5s, [this](){
        auto data = onTPHHandler();
        sixPack->send(
            SixPackLib::Events::TPH(
                data.temperature,
                data.humidity,
                data.pressure
            )
        );
    });
}