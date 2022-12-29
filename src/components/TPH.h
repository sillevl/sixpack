#pragma once

#include "Component.h"
#include "BME280.h"

class TPH: public Component {
    public:
        TPH(BME280* tph);
        void onRegister() override;
    private:
        BME280* tph;
};