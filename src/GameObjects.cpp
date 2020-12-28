#include "GameObjects.h"
#include <iostream>

using std::cout;
using std::endl;

GameObject::GameObject (int side) {
  cout << "consturctor GameObject" << endl;
  m_sampleRect = new SDL_Rect();
  m_side = side;

  if (side == 0) {
    m_sampleRect->x = 0;
    m_sampleRect->y = (H - PLAYER_H) / 2;
  }
  else {
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
  m_delta = 5;
//  m_radius = std::sqrt(PLAYER_H * PLAYER_H + PLAYER_W * PLAYER_W) / 2.0;
  m_radius = PLAYER_W / 2;
  set_center();
}


void GameObject::set_center() {
  center.x = m_sampleRect->x + PLAYER_W / 2;
  center.y = m_sampleRect->y + PLAYER_H / 2;
}

void GameObject::set_move(int &key) {

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

void GameObject::disable_move(int &key) {
  switch (key)
  {
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

void GameObject::moving() {
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