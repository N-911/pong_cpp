#ifndef PONG_SRC_BOT_H_
#define PONG_SRC_BOT_H_

#include "GameObjects.h"

class Bot : public GameObject
{
 public:
  Bot(int side);
  virtual ~Bot() {}

  void moving() override;

  void set_move(int &key) override;
  void disable_move(int &key) override;
  void move_bot(int x, int y);
};


#endif //PONG_SRC_BOT_H_
