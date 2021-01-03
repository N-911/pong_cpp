#ifndef PONG_SRC_PLAYER_H_
#define PONG_SRC_PLAYER_H_
#include "GameObjects.h"

class Player : public GameObject<SDL_Rect> {
 public:

  Player();
  virtual ~Player();

  void moveUp();
  void moveDown();
  void stop();

};

#endif //PONG_SRC_PLAYER_H_
