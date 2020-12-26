#ifndef PONG_SRC_BALL_H_
#define PONG_SRC_BALL_H_

#include <SDL_rect.h>
#include "Settings.h"

class Ball {

 public:
  Ball(int side);
  virtual ~Ball();

  void moving();
  SDL_Rect* get_rect() const {return m_sampleRect;}

 private:
  SDL_Rect* m_sampleRect;
  Vec2i		pos;
  Vec2i		center;
  Vec2f		speed;
  int		radius;

  void set_center();
  void set_rect();

};

#endif //PONG_SRC_BALL_H_
