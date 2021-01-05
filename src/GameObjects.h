#ifndef PONG_SRC_GAMEOBJECTS_H_
#define PONG_SRC_GAMEOBJECTS_H_

#include <memory>
#include "Settings.h"
#include <SDL.h>
#include <SDL_image.h>

class Ball;

template <typename T>
class GameObject {

 public:
  // Constructors
  GameObject() {
    m_object = new SDL_Rect();
  }
//  GameObject() = default;
  GameObject(GameObject &other) = delete;
  GameObject &operator=(GameObject &other) = delete;
  GameObject(GameObject &&other) = delete;
  GameObject &operator=(GameObject &&other) = delete;

  // Destructor
  ~GameObject() {
    delete m_sampleRect;
  }

  Vec2i velocity() const { return m_velocity;}

  // modify
  void setVelocity(Vec2i v) { m_velocity = v; }
  void setSpeed(int s) { m_speed = s; }
  void set_x(int n);
  void set_y(int n);

  void move();
  void updateBoundingBox();

//  virtual void set_center();
  void set_move(int &key);
  virtual void moving();
  virtual void moving(std::shared_ptr<Ball> ball) { };
//  virtual void move_start();
  virtual void disable_move(int &key);
//  void check_colision(std::shared_ptr<Ball> m_ball);
  SDL_Rect *get_rect() { return m_object; }
//  Vec2i get_center() const { return center; }
//  Vec2f get_speed() const { return speed; }
//  double get_radius() const { return m_radius; }

 protected:
  int m_delta;
  //  double m_radius;  // radius circle in AABB
  SDL_Rect *m_sampleRect;
  bool m_move_up;
  bool m_move_down;
  bool m_move_left;
  bool m_move_right;
  Vec2i center;

  Vec2f m_speed;
//  int m_speed;

  // ===========
  int m_x;
  int m_y;
  Vec2i m_velocity;
  T* m_object;

};

template <typename T>
void GameObject<T>::move() {
  m_x += m_velocity.x;
  m_x += m_velocity.y;
  updateBoundingBox();
}

template <typename T>
void GameObject<T>::set_x(int n) {
  m_x = n;
  updateBoundingBox();
}

template <typename T>
void GameObject<T>::set_y(int n) {
  m_y = n;
  updateBoundingBox();
}

template <typename T>
void GameObject<T>::set_move(int &key) {

  switch (key) {
    case SDLK_UP:m_move_up = true;
      m_speed.y = -10;
    case SDLK_w:m_move_up = true;
      m_speed.y = -10;
      break;
    case SDLK_DOWN:m_move_down = true;
      m_speed.y = 10;
    case SDLK_s:m_move_down = true;
      m_speed.y = 10;
      break;
    case SDLK_RIGHT:m_move_right = true;
      m_speed.x = 10;
    case SDLK_d:m_move_right = true;
      m_speed.x = 10;
      break;
    case SDLK_LEFT:m_move_left = true;
      m_speed.x = -10;
    case SDLK_a:m_move_left = true;
      m_speed.x = -10;
      break;
  }
}
template<typename T>
void GameObject<T>::disable_move(int &key) {
  switch (key) {
    case SDLK_UP:m_move_up = false;
      m_speed.y = 0;
    case SDLK_w:m_move_up = false;
      m_speed.y = 0;
      break;
    case SDLK_DOWN:m_move_down = false;
      m_speed.y = 0;
    case SDLK_s:m_move_down = false;
      m_speed.y = 0;
      break;
    case SDLK_RIGHT:m_move_right = false;
      m_speed.x = 0;
    case SDLK_d:m_move_right = false;
      m_speed.x = 0;
      break;
    case SDLK_LEFT:m_move_left = false;
      m_speed.x = 0;
    case SDLK_a:m_move_left = false;
      m_speed.x = 0;
      break;
  }
}
template<typename T>
void GameObject<T>::moving() {
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
//  set_center();
}

#endif //PONG_SRC_GAMEOBJECTS_H_
