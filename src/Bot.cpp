#include "Bot.h"
#include <iostream>

using std::cout;
using std::endl;

Bot::Bot(int side) : GameObject(side) {
  cout << "consturctor Player" << endl;
}

/*
void Bot::set_move(int &key) {  // key - y
  if (key > center.y)
  {
    m_move_up = false;
    m_move_down = true;
    speed.y = 10;
  }
  else if (key < center.y)
  {
    m_move_up = true;
    m_move_down = false;
    speed.y = -10;
  }
  if (center.y < key + m_delta && center.y > key - m_delta)
  {
    m_move_up = false;
    m_move_down = false;
  }
}

void Bot::disable_move(int &key) {  // key = x
  if (key < W / 2 + BALL_SIZE)  // ball on the left side
  {
    m_move_down = false;
    m_move_up = false;
    speed.y = 0;
  }
}


 */

void Bot::moving(int x, int y) {
//  cout << "bot x = " << m_sampleRect->x << "  y = " << m_sampleRect->y << endl;
  if (x + BALL_SIZE / 2 < H / 2) {
    return;
  }
  else if (y + PLAYER_H /4 > center.y) {
    m_sampleRect->y += m_delta;
  } else {
    m_sampleRect->y -= m_delta;
  }
  set_center();
}


//void Bot::move_bot(int x, int y) {
//    if (x + BALL_SIZE / 2 < H / 2) {
//      return;
//    }
//    else if (y + PLAYER_H /4 > center.y) {
//      m_sampleRect->y += m_delta;
//    } else {
//      m_sampleRect->y -= m_delta;
//    }
//      set_center();
//}
