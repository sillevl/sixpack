#pragma once

#include "Component.h"

struct TPHData {
    float temperature;
    float humidity;
    float pressure;
};
class TPH: public Component {
    public:
        void setTPHHandler( Callback<TPHData()> handler);
    private:
        Callback<TPHData()> onTPHHandler;
};