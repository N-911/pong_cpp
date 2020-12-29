#ifndef PONG_SRC_BOT_H_
#define PONG_SRC_BOT_H_

#include "GameObjects.h"

class Bot : public GameObject
{
 public:
  Bot(int side);
  virtual ~Bot() {}

  void moving(int x, int y) override;
};


#endif //PONG_SRC_BOT_H_
