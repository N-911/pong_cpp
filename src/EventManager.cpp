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

void EventManager::Notify()
{
    for (auto observer : m_list_observer) {
//        observer->UpdateStatus(m_event_type);
    }
}
void EventManager::ChangeStatus(Uint32 event)
{
    m_event_type = event;
    Notify();
}



