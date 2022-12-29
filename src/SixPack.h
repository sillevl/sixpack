#pragma once

#include "mbed.h"
#include "Stm32UniqueId.h"
#include "Messages/Message.h"
#include "Blik.h"
#include "./components/Component.h"
#include <list>
#include <map>

class Component;

static const auto AliveInterval = 10s;

class SixPack {
    public:
        SixPack(CAN* can, events::EventQueue* ev_queue);
        void registerComponent(Component* component);
        void unregisterComponent(Component* component);

        void send(SixPackLib::SixPackMessage);
        void onActivity(mbed::Callback<void()> cb);
        void onMessage(uint32_t type, mbed::Callback<void(SixPackLib::SixPackMessage)> cb);

        void setDeviceType(uint16_t deviceType);
        void setFirmwareVersion(uint16_t firmwareVersion);

    // protected:
        EventQueue queue;

    private:
        Blik blik;
        std::list<Component*> components;
        uint16_t deviceId = 0;
        uint16_t deviceType = 0;
        uint16_t firmwareVersion = 0;

        mbed::Callback<void()> activityCallback;
        std::map<uint32_t, mbed::Callback<void(SixPackLib::SixPackMessage)>> onMessageMap;

        void parseMessage(BlikMessage message);
        void setDeviceId();
        void sendAliveMessage();
};
