#ifndef PONG_SRC_PLAYER_H_
#define PONG_SRC_PLAYER_H_
#include "Settings.h"
#include "GameObjects.h"

class Player : public GameObject {
 public:

  Player(int side);
  virtual ~Player();

//  virtual void set_move(int &key);
//  virtual void moving();
//  virtual void move_start();
//  virtual void disable_move(int &key);

//  virtual SDL_Rect* get_rect() {return m_sampleRect;}
//  virtual Vec2i get_center() const { return center; }
//  Vec2f get_speed() const { return speed; }
//  double get_radius() const { return m_radius; }

//  Vec2i		center;
//  Vec2f		speed;
//  double	m_radius;  // radius circle around AABB
//  virtual void set_center();
//  SDL_Rect* m_sampleRect;

 private:
//  int m_side;
//  int m_delta;
//  int m_left_border;  // border for move player
//  int m_right_border;
//  int m_score;

//  bool m_move_up;
//  bool m_move_down;
//  bool m_move_left;
//  bool m_move_right;


};



#endif //PONG_SRC_PLAYER_H_
