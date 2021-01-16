#ifndef PONG_IOBSERVER_H
#define PONG_IOBSERVER_H

#include <string>
#include <SDL_types.h>
#include <SDL_events.h>

class IObserver
{
public:
  virtual ~IObserver() { };
  virtual void UpdateStatus(SDL_Event& event) = 0;

protected:
    static int m_observer_id;
};

#endif //PONG_IOBSERVER_H
