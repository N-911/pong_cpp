#ifndef PONG_SRC_PLAYER_H_
#define PONG_SRC_PLAYER_H_
#include "Settings.h"

class Player {
 public:
  Player(int side);

  virtual ~Player();

  void set_move(int &key);
  void moving();
  void disable_move(int &key);
  SDL_Rect* get_rect() const {return m_sampleRect;}
  Vec2i get_center() const { return center; }
  Vec2f get_speed() const { return speed; }
  double get_radius() const { return m_radius; }
  Vec2i		pos;
  Vec2i		center;
  Vec2f		speed;
  double	m_radius;  // radius circle around AABB
  void set_center();
 private:
//  Box m_block;
  SDL_Rect* m_sampleRect;


  int m_delta;
  int m_left_border;  // border for move player
  int m_right_border;
  int m_score;

  bool m_move_up;
  bool m_move_down;
  bool m_move_left;
  bool m_move_right;


};

#endif //PONG_SRC_PLAYER_H_
