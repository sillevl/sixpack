#pragma once

namespace spha {
    enum deviceTypes {
        SPHA_GW         = 0x0001,     // SPHA Gateway
        SPHA_BTNN       = 0x0100,     // SPHA Button Niko
        SPHA_BTNU       = 0x0101,     // SPHA Button Universal
        SPHA_BTNI       = 0x0150,     // SPHA Button Interface (DIN)
        SPHA_REL6       = 0x0200,     // SPHA Relay 6 Module (DIN)
        SPHA_REL12      = 0x0201     // SPHA Relay 12 Module (DIN)
    };
};