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
  center.x = m_sampleRect->x + BALL_SIZE / 2;
  center.y = m_sampleRect->y + BALL_SIZE / 2;

  /* для дебага застрявания в углу бота*/
  if (center.x < 0 || center.x > W)
  {
    cout << "attention " << endl;
    m_sampleRect->y -= 30;
  }
}

Ball::~Ball() {
 delete m_sampleRect;
}

void Ball::moving() {
//  cout << " ball  before moving x =" <<  pos.x << "y ="  << pos.y << endl;
  if (m_sampleRect->x - BALL_SIZE/ 2 < 0 || m_sampleRect->x + BALL_SIZE >= W)
  {
    speed.x = -speed.x;
    cout << "ball x =" <<  m_sampleRect->x << "    y ="  << m_sampleRect->y << endl;
//    Mix_PlayMusic(bum, 0);
  }
  if (m_sampleRect->y + speed.y < 0 || m_sampleRect->y + BALL_SIZE + speed.y >= H)
  {
    speed.y = -speed.y;
//    Mix_PlayMusic(bum, 0);
  }
  m_sampleRect->x += (int)speed.x;
  m_sampleRect->y += (int)speed.y;
//  speed.x *= BRAKING;
//  speed.y *= BRAKING;

  if (m_sampleRect->x < 0)
    m_sampleRect->x = 0;
  else if (m_sampleRect->x >= W)
    m_sampleRect->x = W - BALL_SIZE;
  set_center();

}


bool Ball::is_movind() const {
  return speed.x != 0 || speed.y != 0;
}

void Ball::set_new_ball(int side) {
  if (side == 0) {
    m_sampleRect->x = W /2;
    m_sampleRect->y = (H - BALL_SIZE ) / 2;
    speed.x = 5;
  }
  else if (side == 1){
    m_sampleRect->x = W - 30;
    m_sampleRect->y = (H - BALL_SIZE) / 2;
    speed.x = -5;
  }
  m_sampleRect->x = m_sampleRect->x;
  m_sampleRect->y = m_sampleRect->y;
  m_sampleRect->w = BALL_SIZE;
  m_sampleRect->h = BALL_SIZE;
  speed.y = 0;
  set_center();
  m_radius = BALL_SIZE / std::sqrt(2.0);
}
void Ball::set_rect_x(int x) {
  m_sampleRect->x = x;
}

void Ball::set_rect_y(int y) {
  m_sampleRect->y = y;
}
void Ball::set_speed_x(int x) {
  speed.x = x;
}
void Ball::set_speed_y(int y) {
  speed.y = y;
}
