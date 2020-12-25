//
// Created by snikolayen on 25.12.2020.
//

#ifndef PONG_SRC_GAME_H_
#define PONG_SRC_GAME_H_

#include "Window.h"
#include "Ball.h"
#include "Player.h"

class Game {
 public:
  Game();
  virtual ~Game();

 private:
  SDL_Event	m_ev;
  SDL_Surface	*m_score_surface;
  SDL_Texture *m_score_texture;

  Window m_window;
  Ball m_ball;
  Player *m_player1;
  Player *m_player2;

  bool		m_close;
  bool		play_mus;
  int	    m_number_pl;

  int showMenu();

};

#endif //PONG_SRC_GAME_H_
