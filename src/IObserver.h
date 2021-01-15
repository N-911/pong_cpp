#ifndef PONG_IOBSERVER_H
#define PONG_IOBSERVER_H

#include <string>
#include <SDL_types.h>

class IObserver
{
public:
  virtual ~IObserver() { };
  virtual void UpdateStatus(Uint32 event) = 0;
};

#endif //PONG_IOBSERVER_H
