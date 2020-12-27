#ifndef PONG_SRC_BALL_H_
#define PONG_SRC_BALL_H_

#include <SDL_rect.h>
#include "Settings.h"

class Ball {

 public:
  Ball(int side);
  virtual ~Ball();

  void moving();
  bool is_movind() const;
  SDL_Rect* get_rect() const {return m_sampleRect;}
  Vec2i get_center() const { return center; }
  Vec2f get_speed() const { return speed; }
  double get_radius() const { return m_radius; }
  void set_new_ball(int side);

  void set_center();
  Vec2i		pos;
  Vec2i		center;
  Vec2f		speed;
  double    m_radius;  // radius circle around AABB ball

 private:
  SDL_Rect* m_sampleRect;


  void set_rect();

};

#endif //PONG_SRC_BALL_H_
