#ifndef PONG_SRC_BOT_H_
#define PONG_SRC_BOT_H_

#include "GameObjects.h"

class Bot : public GameObject {
 public:
  Bot(int side);
  virtual ~Bot() {}

  void moving(std::shared_ptr<Ball> ball) override;
};

#endif //PONG_SRC_BOT_H_
