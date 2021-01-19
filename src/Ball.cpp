#include "Ball.h"
#include <cmath>
#include <iostream>

using std::cout;
using std::endl;

Ball::Ball(int x, int y)
{
    // m_x, m_ y  centre circle, m_radius - radius
    m_x = W / 2;
    m_y = H / 2;

    update_box();
    m_object->w = BALL_SIZE;
    m_object->h = BALL_SIZE;
    m_speed = 5;
    m_radius = BALL_SIZE / 2;
//    set_velocity(Vec2i{m_speed, m_speed});
    set_rand_velocity();
}

void Ball::update_box()
{
    m_object->x = m_x - m_radius;
    m_object->y = m_y - m_radius;
}

void Ball::move()
{
    // down
    if ((m_y + m_velocity.y) >= H) {
        m_velocity.y = -m_velocity.y;
        m_y = H - m_radius;
    }
        // top
    else if ((m_y + m_velocity.y) < 0) {
        m_velocity.y = -m_velocity.y;
        m_y = m_radius;
    }
    else
        m_y += m_velocity.y;

    m_x += m_velocity.x;
    update_box();
//    cout << "ball x =" << m_object->x << " ball y =" << m_object->y << endl;
//    cout << "ball x =" << m_x << " ball y =" << m_y << endl;
}

void Ball::set_new_ball(int side)
{
    set_rand_velocity();
    if (side == 0) {
        m_velocity.x = -m_speed;
    }
    else if (side == 1) {
        m_velocity.x = m_speed;
    }
    m_x = W / 2;
    m_y = H / 2;

    cout << "ball velocity x =" << m_velocity.x << " y =" << m_velocity.y << endl;
    update_box();
}
void Ball::set_rand_velocity()
{
    int _rand = m_rdevice();
    m_mt.seed(_rand);

    std::uniform_int_distribution<int> dist(0, 1);

    if (dist(m_mt) == 1)
        m_velocity.x = m_speed;
    else
        m_velocity.x = -m_speed;

    std::uniform_int_distribution<int> dist2(-3, 3);
    m_velocity.y = dist2(m_mt);

}

Circle Ball::get_ball_geomerty() const
{
    return {m_x, m_y, m_radius};
}

Vec2i Ball::check_colision(Circle ball) const
{
    return {0, 0};
}


/*


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

 */