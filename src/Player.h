#ifndef PONG_SRC_PLAYER_H_
#define PONG_SRC_PLAYER_H_
#include "GameObjects.h"

class Player : public GameObject<SDL_Rect> {
 public:

  Player(int side);
  virtual ~Player();


};

#endif //PONG_SRC_PLAYER_H_
