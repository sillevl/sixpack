#include "Stm32UniqueId.h"

uint8_t* Stm32UniqueId::getId() {
    uint8_t* uid_reg = (uint8_t*)0x1FFF7590;
    return uid_reg;
}