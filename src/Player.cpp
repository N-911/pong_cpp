#include <SDL_quit.h>
#include <SDL_rect.h>
#include "Player.h"
#include "Window.h"
#include <iostream>
#include <cmath>

using std::cout;
using std::endl;

Player::Player(int side) {
  cout << "consturctor Player" << endl;
  m_sampleRect = new SDL_Rect();
  if (side == 0) {
    m_left_border = 0;
    m_right_border = W / 2;
    pos.x = 0;
    pos.y = (H - PLAYER_H ) / 2;
    m_sampleRect->x = 0;
    m_sampleRect->y = (H - PLAYER_H) / 2;
  }
  else {
    m_sampleRect->x = W - PLAYER_W;
    m_sampleRect->y = (H - PLAYER_H) / 2;
    m_left_border = W / 2;
    m_right_border = W;
    pos.x = W - PLAYER_W;
    pos.y = (H - PLAYER_H ) / 2;
  }
  m_sampleRect->w = PLAYER_W;
  m_sampleRect->h = PLAYER_H;
  speed.x = 0;
  speed.y = 0;

  m_move_up = false;
  m_move_down = false;
  m_move_left = false;
  m_move_right = false;
  m_delta = 5;
  m_radius = std::sqrt(PLAYER_H * PLAYER_H + PLAYER_W * PLAYER_W) / 2.0;
  m_score = 0;

  set_center();
}

void Player::set_center() {
  center.x = pos.x + PLAYER_W / 2;
  center.y = pos.y + PLAYER_H / 2;
}


Player::~Player()
{
}

void Player::set_move(int &key) {

    switch (key) {
      case SDLK_UP:
        m_move_up = true;
        speed.y = -10;
      case SDLK_w:
        m_move_up = true;
        speed.y = -10;
        break;
      case SDLK_DOWN:
        m_move_down = true;
        speed.y = 10;
      case SDLK_s:
        m_move_down = true;
        speed.y = 10;
        break;
      case SDLK_RIGHT:
        m_move_right = true;
        speed.x = 10;
      case SDLK_d:
        m_move_right = true;
        speed.x = 10;
        break;
      case SDLK_LEFT:
        m_move_left = true;
        speed.x = -10;
      case SDLK_a:
        m_move_left = true;
        speed.x = -10;
        break;
    }
}

void Player::disable_move(int &key) {
  switch (key) {
    case SDLK_UP:
      m_move_up = false;
      speed.y = 0;
    case SDLK_w:
      m_move_up = false;
      speed.y = 0;
      break;
    case SDLK_DOWN:
      m_move_down = false;
      speed.y = 0;
    case SDLK_s:
      m_move_down = false;
      speed.y = 0;
      break;
    case SDLK_RIGHT:
      m_move_right = false;
      speed.x = 0;
    case SDLK_d:
      m_move_right = false;
      speed.x = 0;
      break;
    case SDLK_LEFT:
      m_move_left = false;
      speed.x = 0;
    case SDLK_a:
      m_move_left = false;
      speed.x = 0;
      break;
  }
}



void Player::moving() {
//  cout << "layer::moving() " << endl;
//  cout << "before moving " << "x =" << m_sampleRect->x << "y =" << m_sampleRect->y;

  if (m_move_up)
  {
    if (m_sampleRect->y - m_delta > 0 )
      m_sampleRect->y -= m_delta;
    else
      m_sampleRect->y = 0;
  }
  if (m_move_down)
  {
    if (m_sampleRect->y + m_delta < H - 50)
      m_sampleRect->y += m_delta;
    else
      m_sampleRect->y = H - 50;
  }
  set_center();
}


