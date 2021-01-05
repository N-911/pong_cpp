#ifndef PONG_SRC_BOT_H_
#define PONG_SRC_BOT_H_

#include "GameObjects.h"

class Ball;

class Bot : public GameObject<SDL_Rect> {

 public:
  Bot();
  virtual ~Bot() {}

  void move_to_ball();
  void moving() override { };

};

#endif //PONG_SRC_BOT_H_
