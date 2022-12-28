
#include "Blik.h"

class IComponent {
    public:
    virtual void onRegister() {};
    virtual void onMessage(BlikMessage message) {};
};