#include "Ball.h"

Ball::Ball(int side) {
  if (side) {
    pos.x = 15;
    pos.y = (H - 15 ) / 2;
  }
  else {
    pos.x = W - 30;
    pos.y = (H - 15 ) / 2;
  }
  m_sampleRect = new SDL_Rect();
  m_sampleRect->x = pos.x;
  m_sampleRect->y = pos.y;
  m_sampleRect->w = 15;
  m_sampleRect->h = 15;
  speed.x = -1.1;
  speed.y = 0;

  radius = 7;
}

Ball::~Ball() {

}
void Ball::moving() {
  if (pos.x + speed.x < 0 || pos.x + 15 + speed.x >= W)
  {
    speed.x = -speed.x;
//    Mix_PlayMusic(bum, 0);
  }
  if (pos.y + speed.y < 0 || pos.y + 64 + speed.y >= H)
  {
    speed.y = -speed.y;
//    Mix_PlayMusic(bum, 0);
  }
  pos.x += (int)speed.x;
  pos.y += (int)speed.y;
  speed.x *= BRAKING;
  speed.y *= BRAKING;
  if (pos.x < 0)
    pos.x = 0;
  else if (pos.x >= W)
    pos.x = W - 1;
  set_center();
  set_rect();
}
void Ball::set_center() {
  center.x = pos.x + radius;
  center.y = pos.y + radius;

  /* для дебага застрявания в углу бота*/
  if (center.x < 0 || center.x > W)
  {
    pos.y -= 30;
  }
}
void Ball::set_rect() {
  m_sampleRect->x = pos.x;
  m_sampleRect->y =pos.y;

}
