#include "Ball.h"
#include <cmath>
#include <iostream>

using std::cout;
using std::endl;

Ball::Ball(int x, int y)
{
    m_x = W / 2;
    m_y = H / 2;
    update_box();
    m_object->w = BALL_SIZE;
    m_object->h = BALL_SIZE;
    m_speed = 5;
    set_velocity(Vec2i{m_speed, m_speed});

}
void Ball::move()
{
    if (((m_y + m_velocity.y) > H) || ((m_y + m_velocity.y) < 0)) {
        m_velocity.y = -m_velocity.y;
    }
    m_y += m_velocity.y;
    m_x += m_velocity.x;
    update_box();
//    cout << "ball x =" << m_object->x << " ball y =" << m_object->y << endl;
    cout << "ball x =" << m_x << " ball y =" << m_y << endl;
}

void Ball::set_new_ball(int side)
{
    if (side == 0) {
        m_velocity.x = -m_speed;
    }
    else if (side == 1) {
        m_velocity.x = m_speed;
//        m_velocity.y = -m_speed;
    }
    m_x = W / 2 - BALL_SIZE / 2;
    m_y = H / 2 + BALL_SIZE / 2;

        cout << "ball velocity x =" << m_velocity.x << " y =" << m_velocity.y << endl;
    update_box();
//    set_center();
//    m_radius = BALL_SIZE / std::sqrt(2.0);
}

/*
void Ball::set_center() {
  center.x = m_sampleRect->x + BALL_SIZE / 2;
  center.y = m_sampleRect->y + BALL_SIZE / 2;
}

void Ball::moving() {
  if (m_sampleRect->y + speed.y <= 0 || m_sampleRect->y + BALL_SIZE + speed.y >= H) {
    speed.y = -speed.y;
  }
  m_sampleRect->x += (int) speed.x;
  m_sampleRect->y += (int) speed.y;

  if (m_sampleRect->x < 0)
    m_sampleRect->x = 0;
  else if (m_sampleRect->x >= W)
    m_sampleRect->x = W - BALL_SIZE;
  set_center();
}

bool Ball::is_movind() const {
  return speed.x != 0 || speed.y != 0;
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

 */