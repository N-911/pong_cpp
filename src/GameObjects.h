#ifndef PONG_SRC_GAMEOBJECTS_H_
#define PONG_SRC_GAMEOBJECTS_H_

#include <memory>
#include "Settings.h"
#include "Ball.h"

struct Circle {
  int x;
  int y;
  int r;
};

struct Vec2d
{
  int x;
  int y;
};

//template <typename T>
class GameObject {

 protected:
  int m_side;
  int m_delta;
  bool m_move_up;
  bool m_move_down;
  bool m_move_left;
  bool m_move_right;
  Vec2i center;
  Vec2f speed;
  double m_radius;  // radius circle in AABB
  SDL_Rect *m_sampleRect;

 public:
  // Constructors
  GameObject(int side);
  GameObject(GameObject &other) = delete;
  GameObject &operator=(GameObject &other) = delete;
  GameObject(GameObject &&other) = delete;
  GameObject &operator=(GameObject &&other) = delete;

  // Destructor
  ~GameObject() {
    delete m_sampleRect;
  }

  virtual void set_center();
  virtual void set_move(int &key);
  virtual void moving();
  virtual void moving(std::shared_ptr<Ball> ball) {int x = ball->get_speed().x;};
  virtual void move_start();
  virtual void disable_move(int &key);
  void check_colision(std::shared_ptr<Ball> m_ball);
  SDL_Rect *get_rect() { return m_sampleRect; }
  Vec2i get_center() const { return center; }
  Vec2f get_speed() const { return speed; }
  double get_radius() const { return m_radius; }
};

#endif //PONG_SRC_GAMEOBJECTS_H_
