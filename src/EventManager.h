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

    virtual void Attach(IObserver *observer) override;
    virtual void Detach(IObserver *observer) override;
    virtual void Notify(SDL_Event& event) override;

private:
    std::list<IObserver *> m_list_observer;
//    SDL_Event* m_event_type;
};

#endif //PONG_EVENTMANAGER_H
