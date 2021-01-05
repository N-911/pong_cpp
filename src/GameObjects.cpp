#include "GameObjects.h"
#include <iostream>

using std::cout;
using std::endl;


/*
GameObject::GameObject() {
  cout << "consturctor GameObject" << endl;
  m_sampleRect = new SDL_Rect();
  m_side = side;

  if (side == 0) {
    m_sampleRect->x = 0;
    m_sampleRect->y = (H - PLAYER_H) / 2;
  } else {
    m_sampleRect->x = W - PLAYER_W;
    m_sampleRect->y = (H - PLAYER_H) / 2;
  }
  m_sampleRect->w = PLAYER_W;
  m_sampleRect->h = PLAYER_H;
  speed.x = 0;
  speed.y = 0;

  m_move_up = false;
  m_move_down = false;
  m_move_left = false;
  m_move_right = false;
//  m_delta = 5;
  m_radius = PLAYER_W / 2;
  set_center();
}
*/

template<>
void GameObject<Circle>::updateBoundingBox() {
  m_object->x = m_x + m_object->r;
  m_object->y = m_y + m_object->r;
}

template<>
void GameObject<SDL_Rect>::updateBoundingBox() {
  m_object->x = m_x;
  m_object->y = m_y;
}


/*
void GameObject::set_center() {
  center.x = m_sampleRect->x + PLAYER_W / 2;
  center.y = m_sampleRect->y + PLAYER_H / 2;
}

 */



/*
void GameObject::moving() {
  if (m_move_up) {
    if (m_sampleRect->y - m_delta > 0)
      m_sampleRect->y -= m_delta;
    else
      m_sampleRect->y = 0;
  }
  if (m_move_down) {
    if (m_sampleRect->y + m_delta < H - 50)
      m_sampleRect->y += m_delta;
    else
      m_sampleRect->y = H - 50;
  }
  set_center();
}

void GameObject::move_start() {
  if (m_side == 0) {
    m_sampleRect->x = 0;
  } else if (m_side == 1) {
    m_sampleRect->x = W - PLAYER_W;
  }
  m_sampleRect->y = H / 2 - PLAYER_H / 2;
  speed.x = 0;
  speed.y = 0;
  set_center();
}

void GameObject::check_colision(std::shared_ptr<Ball> m_ball) {

  double Dx = m_ball->get_center().x - this->get_center().x;
  double Dy = m_ball->get_center().y - this->get_center().y;
  double d = sqrt(Dx * Dx + Dy * Dy);

  if (d == 0)
    d = 0.01;

  if (d <= m_ball->get_radius() + this->get_radius()) {
    double cos_a = Dx / d;
    double sin_a = Dy / d;
    double Vn1 = this->get_speed().x * cos_a + this->get_speed().y * sin_a;
    double Vn2 = m_ball->get_speed().x * cos_a + m_ball->get_speed().y * sin_a;

    double dt = (m_ball->get_radius() + this->get_radius() - d) / (Vn1 - Vn2);
    if (dt > 0.6)
      dt = 0.6;
    else if (dt < -0.6)
      dt = -0.6;

    this->get_rect()->x -= this->get_speed().x * dt;
    this->get_rect()->y -= this->get_speed().y * dt;
    this->set_center();

    m_ball->set_rect_x(m_ball->get_rect()->x - m_ball->get_speed().x * dt);
    m_ball->set_rect_y(m_ball->get_rect()->y - m_ball->get_speed().y * dt);
    m_ball->set_center();

    Dx = m_ball->get_center().x - this->get_center().x;
    Dy = m_ball->get_center().y - this->get_center().y;
    d = sqrt(Dx * Dx + Dy * Dy);
    if (d == 0)
      d = 0.01;

    cos_a = Dx / d;
    sin_a = Dy / d;

    Vn1 = this->get_speed().x * cos_a + this->get_speed().y * sin_a;
    Vn2 = m_ball->get_speed().x * cos_a + m_ball->get_speed().y * sin_a;

    double Vt2 = -m_ball->get_speed().x * sin_a + m_ball->get_speed().y * cos_a;

    if (Vn2 < 0)
      Vn2 = Vn1 - Vn2;
    else
      Vn2 += Vn1;

    m_ball->set_speed_x(Vn2 * cos_a - Vt2 * sin_a);
    m_ball->set_speed_y(Vn2 * sin_a + Vt2 * cos_a);

    this->get_rect()->x += this->get_speed().x * dt;
    this->get_rect()->y += this->get_speed().y * dt;
    this->set_center();

    if (m_ball->get_speed().x > 50)
      m_ball->set_speed_x(50);
    if (m_ball->get_speed().x < -50)
      m_ball->set_speed_x(-50);
    if (m_ball->get_speed().y > 50)
      m_ball->set_speed_y(50);
    if (m_ball->get_speed().y < -50)
      m_ball->set_speed_y(-50);

    m_ball->get_rect()->x += m_ball->get_speed().x * dt;
    m_ball->get_rect()->y += m_ball->get_speed().y * dt;
    m_ball->set_center();
  }

}
  */
