#include "Ball.h"
#include <cmath>
#include <iostream>

using std::cout;
using std::endl;

Ball::Ball(int side) {
  set_new_ball(side);
}

void Ball::set_center() {
  center.x = pos.x + SIZE_BALL / 2;
  center.y = pos.y + SIZE_BALL / 2;

  /* для дебага застрявания в углу бота*/
  if (center.x < 0 || center.x > W)
  {
    cout << "attention " << endl;
    pos.y -= 30;
  }
}


Ball::~Ball() {

}
void Ball::moving() {
  if (pos.x + speed.x < 0 || pos.x + SIZE_BALL + speed.x >= W)
  {
    speed.x = -speed.x;
//    Mix_PlayMusic(bum, 0);
  }
  if (pos.y + speed.y < 0 || pos.y + SIZE_BALL + speed.y >= H)
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
    pos.x = W - SIZE_BALL;
  set_rect();
  set_center();
}

void Ball::set_rect() {
  m_sampleRect->x = pos.x;
  m_sampleRect->y = pos.y;

}
bool Ball::is_movind() const {
  return speed.x != 0 || speed.y != 0;
}
void Ball::set_new_ball(int side) {
  if (side) {
    pos.x = W /2;
    pos.y = (H - SIZE_BALL ) / 2;
  }
  else {
    pos.x = W - 30;
    pos.y = (H - SIZE_BALL) / 2;
  }
  m_sampleRect = new SDL_Rect();
  m_sampleRect->x = pos.x;
  m_sampleRect->y = pos.y;
  m_sampleRect->w = SIZE_BALL;
  m_sampleRect->h = SIZE_BALL;
//  speed.x = -1.1;
  speed.x = -20;
  speed.y = -10;
  set_center();
  m_radius = SIZE_BALL / std::sqrt(2.0);
}
