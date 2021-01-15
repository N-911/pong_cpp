#ifndef PONG_EVENTMANAGER_H
#define PONG_EVENTMANAGER_H

#include <list>
#include "IEventManager.h"
#include <SDL_events.h>
//#include "IObserver.h"

class EventManager : public IEventManager {
public:

    EventManager() = default;
    virtual ~EventManager();

   void ChangeStatus(Uint32 event);

    virtual void Attach(IObserver *observer) override;
    virtual void Detach(IObserver *observer) override;
    virtual void Notify() override;

private:
    std::list<IObserver *> m_list_observer;
    Uint32 m_event_type;
};

#endif //PONG_EVENTMANAGER_H
