#ifndef PONG_SRC_GAME_H_
#define PONG_SRC_GAME_H_
#include "Window.h"
#include "Ball.h"
#include "Player.h"
#include <memory>
#include "Settings.h"

class Game {

 public:
  Game();
  virtual ~Game();
  bool run() const {return m_run;}
  void main_loop();

  void events();
  void draw();
  void Exit();

 private:
  SDL_Event	m_ev;
  Window m_window;
//  SDL_Rect m_sampleRect;

  std::shared_ptr<Ball> m_ball;
  std::shared_ptr<Player> m_player_left;
  std::shared_ptr<Player> m_player_right;

  SDL_Surface *m_score_surface;
  SDL_Texture *m_score_texture;
  SDL_Surface *m_text_surface[2];
  SDL_Texture *m_text_texture[2];
  SDL_Color m_text_color;
  SDL_bool m_loop;

  SDL_bool _inSampleRect = SDL_FALSE;

  unsigned int m_color[WIDTH * HEIGHT];
  bool		m_run;
  bool		play_mus;
  int	    m_number_pl;

  int show_menu();
  void on_event(SDL_Event& event);

  void draw_score();
  bool check_goal() const;
  void colision(std::shared_ptr<Player> player);
};

#endif //PONG_SRC_GAME_H_
