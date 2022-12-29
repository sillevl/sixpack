#pragma once

#include "Blik.h"
#include "SixPack.h"
#include "mbed_trace.h"

class SixPack;

class Component {
    public:
        virtual void onRegister();
        // virtual void onMessage(BlikMessage message) {};
        void setSixPack(SixPack* sixPack);

    protected:
        SixPack* sixPack;
};