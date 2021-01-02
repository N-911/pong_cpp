#ifndef PONG_SRC_GAME_H_
#define PONG_SRC_GAME_H_
#include "Window.h"
#include "Ball.h"
#include "Player.h"
#include <memory>
#include "GamePlayController.h"
#include "GameObjects.h"
#include "Bot.h"

class Game {
 public:
  Game();
  virtual ~Game();
  void game_loop();

 private:
  SDL_Event m_ev;
  Window m_window
  ;
  int frameCount;
  unsigned int lastFrame;
  int fps;

  bool m_pause;

  std::unique_ptr<Ball> m_ball;
  std::unique_ptr<Player> m_left;
  std::unique_ptr<Player> m_right;

//  std::unique_ptr<Label>  _scoreLabel;
//  std::unique_ptr<Label> _countdownTimer;
//  std::unique_ptr<Label> _controlsLabel

//  std::shared_ptr<Ball> m_ball;
//  Player *m_player_left;
//  GameObject *m_current_player_right;

  GamePlayController *m_game_play;
  SDL_Surface *m_score_surface;
  SDL_Texture *m_score_texture;
  SDL_Color m_text_color;
  SDL_bool m_loop;
  SDL_Rect m_score_board;
  int m_number_pl;
//  bool		play_mus;

  int show_menu();
  void on_event(SDL_Event &event);
  void update();
  void render(float interpolation);
  void draw_score();
  int check_goal();
};

#endif //PONG_SRC_GAME_H_
