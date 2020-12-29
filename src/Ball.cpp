#include "Ball.h"
#include <cmath>
#include <iostream>

using std::cout;
using std::endl;

Ball::Ball(int side) {
  m_sampleRect = new SDL_Rect();
  set_new_ball(side);
}

void Ball::set_center() {
  center.x = pos.x + BALL_SIZE / 2;
  center.y = pos.y + BALL_SIZE / 2;

  /* для дебага застрявания в углу бота*/
  if (center.x < 0 || center.x > W)
  {
    cout << "attention " << endl;
    pos.y -= 30;
  }
}

Ball::~Ball() {
 delete m_sampleRect;
}

void Ball::moving() {
//  cout << " ball  before moving x =" <<  pos.x << "y ="  << pos.y << endl;
  if (pos.x - BALL_SIZE/ 2 < 0 || pos.x + BALL_SIZE >= W)
  {
    speed.x = -speed.x;
    cout << "ball x =" <<  pos.x << "    y ="  << pos.y << endl;
//    Mix_PlayMusic(bum, 0);
  }
  if (pos.y + speed.y < 0 || pos.y + BALL_SIZE + speed.y >= H)
  {
    speed.y = -speed.y;
//    Mix_PlayMusic(bum, 0);
  }
  pos.x += (int)speed.x;
  pos.y += (int)speed.y;
//  speed.x *= BRAKING;
//  speed.y *= BRAKING;

  if (pos.x < 0)
    pos.x = 0;
  else if (pos.x >= W)
    pos.x = W - BALL_SIZE;
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
  if (side == 0) {
    pos.x = W /2;
    pos.y = (H - BALL_SIZE ) / 2;
    speed.x = 5;
  }
  else if (side == 1){
    pos.x = W - 30;
    pos.y = (H - BALL_SIZE) / 2;
    speed.x = -5;
  }
  m_sampleRect->x = pos.x;
  m_sampleRect->y = pos.y;
  m_sampleRect->w = BALL_SIZE;
  m_sampleRect->h = BALL_SIZE;
  speed.y = 0;
  set_center();
  m_radius = BALL_SIZE / std::sqrt(2.0);
}
