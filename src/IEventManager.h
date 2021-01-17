#ifndef PONG_IEVENTMANAGER_H
#define PONG_IEVENTMANAGER_H

#include "IObserver.h"

class IEventManager {
public:
    virtual ~IEventManager() { };
    virtual void attach(IObserver* observer) = 0;
    virtual void detach(IObserver* observer) = 0;
    virtual void notify(SDL_Event& event) = 0;
};

#endif //PONG_IEVENTMANAGER_H
