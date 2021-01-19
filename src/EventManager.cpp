#include "EventManager.h"
#include "iostream"

using std::cout;

EventManager::~EventManager()
{
    cout << "EventManager destructor";
}

void EventManager::attach(IObserver* observer)
{
    m_list_observer.push_back(observer);
}
void EventManager::detach(IObserver* observer)
{
    m_list_observer.remove(observer);
}

void EventManager::notify(SDL_Event& event)
{
    for (auto observer : m_list_observer) {
        observer->update_status(event);
    }
}

void EventManager::ChangeStatus(SDL_Event& event)
{
    notify(event);
}



