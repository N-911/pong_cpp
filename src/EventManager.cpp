#include "EventManager.h"
#include "iostream"

using std::cout;

EventManager::~EventManager()
{
    cout << "EventManager destructor";
}

void EventManager::Attach(IObserver* observer)
{
    m_list_observer.push_back(observer);
}
void EventManager::Detach(IObserver* observer)
{
    m_list_observer.remove(observer);
}

void EventManager::Notify(SDL_Event& event)
{
    for (auto observer : m_list_observer) {
        observer->UpdateStatus(event);
    }
}

void EventManager::ChangeStatus(SDL_Event& event)
{
//    m_event_type = event;
    Notify(event);
}



