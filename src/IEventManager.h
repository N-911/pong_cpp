#ifndef PONG_IEVENTMANAGER_H
#define PONG_IEVENTMANAGER_H

#include "IObserver.h"

class IEventManager {
    public:
        virtual ~IEventManager() {};
        virtual void Attach(IObserver *observer) = 0;
        virtual void Detach(IObserver *observer) = 0;
        virtual void Notify() = 0;
    };

#endif //PONG_IEVENTMANAGER_H
