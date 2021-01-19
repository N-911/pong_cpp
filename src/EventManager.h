#ifndef PONG_EVENTMANAGER_H
#define PONG_EVENTMANAGER_H

#include <list>
#include "IEventManager.h"
#include <SDL_events.h>

class EventManager : public IEventManager {
public:

    EventManager() = default;
    virtual ~EventManager();

    void ChangeStatus(SDL_Event& event);
    virtual void attach(IObserver* observer) override;
    virtual void detach(IObserver* observer) override;
    virtual void notify(SDL_Event& event) override;

private:
    std::list<IObserver*> m_list_observer;
};

#endif //PONG_EVENTMANAGER_H
