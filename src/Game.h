#ifndef PONG_SRC_GAME_H_
#define PONG_SRC_GAME_H_
#include "Window.h"
#include "Ball.h"
#include "Player.h"
#include <memory>
#include "Settings.h"
#include "GamePlayController.h"
#include "GameObjects.h"
#include "Bot.h"

class Game {

 public:
  Game();
  virtual ~Game();
  void game_loop();

 private:
  SDL_Event	m_ev;
  Window m_window;
  int frameCount;
  int timerFPS;
  int lastFrame;
  int fps;
  bool m_pause;

  std::shared_ptr<Ball> m_ball;
  std::shared_ptr<Player> m_player_left;
  std::shared_ptr<GameObject> m_player_right;
//  std::shared_ptr<Bot> m_player_right_bot;
  std::shared_ptr<Bot> m_player_right_bot2;

//  Player* m_player_left;
//  Player* m_player_right;
//  Bot* m_player_right_bot;


  GamePlayController* m_game_play;

  SDL_Surface *m_score_surface;
  SDL_Texture *m_score_texture;

  SDL_Color m_text_color;
  SDL_bool m_loop;
  SDL_Rect m_score_board;

  SDL_bool _inSampleRect = SDL_FALSE;
  bool		play_mus;
  int	    m_number_pl;

  int show_menu();
  void on_event(SDL_Event& event);

  void update();
  void render();
  void draw_score(int x, int y);

  bool check_goal();
  void colision(std::shared_ptr<Player> player);
  void colision2(std::shared_ptr<Bot> player);

//  bool run() const {return m_run;}
  void Exit();

};

#endif //PONG_SRC_GAME_H_
