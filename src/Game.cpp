#include "Game.h"
#include <iostream>
#include "Bot.h"

using std::cout;
using std::endl;

Game::Game() {
  cout << "Game Constructor" << endl;
  m_loop = SDL_TRUE;
  m_number_pl = 1;
  m_game_play = new GamePlayController();

//  m_number_pl = show_menu();
  m_text_color = (SDL_Color) {255, 255, 0, 255};
  m_player_left = std::shared_ptr<Player>(new Player(0));

  if (m_number_pl == 1) {
//    m_player_right = std::shared_ptr<GameObject>(new Bot(1));
    m_player_right_bot2 = std::shared_ptr<Bot>(new Bot(1));
  } else {
    m_player_right = std::shared_ptr<GameObject>(new Player(1));
  }
  m_ball  = std::shared_ptr<Ball>(new Ball(1));
  m_pause = false;

}

Game::~Game() {
  cout << "Game Destructor" << endl;
  delete m_game_play;
}

int Game::show_menu() {
  SDL_Surface *screen = SDL_CreateRGBSurface(0, W, H, 32, 0, 0, 0, 0);
  SDL_Texture *texture;

  int x, y;
  const int num_menu = 2;
  const char *menu_point[num_menu] = {"Single Player", "Multiplayer"};

  bool selected[num_menu] = {0, 0};
  SDL_Color color[2] = {{255, 255, 255, 0}, {255, 0, 0, 0}};

  SDL_Surface *menus[num_menu];

  menus[0] = TTF_RenderText_Solid(m_window.getShrift(), menu_point[0], color[0]);
  menus[1] = TTF_RenderText_Solid(m_window.getShrift(), menu_point[1], color[0]);

  SDL_Rect pos[num_menu];

  pos[0].x = screen->clip_rect.w / 2 - menus[0]->clip_rect.w / 2;
  pos[0].y = screen->clip_rect.h / 2 - menus[0]->clip_rect.h;
  pos[1].x = screen->clip_rect.w / 2 - menus[0]->clip_rect.w / 2;
  pos[1].y = screen->clip_rect.h / 2 + menus[0]->clip_rect.h;

  SDL_FillRect(screen, &screen->clip_rect, SDL_MapRGB(screen->format, 0x00, 0x00, 0x00));

  while (1) {
    while (SDL_PollEvent(&m_ev)) {
      switch (m_ev.type) {
        case SDL_QUIT:
          SDL_FreeSurface(menus[0]);
          SDL_FreeSurface(menus[1]);
          SDL_FreeSurface(screen);
          SDL_DestroyTexture(texture);
          m_loop = SDL_FALSE;
          return (0);

        case SDL_KEYDOWN:
          if (m_ev.key.keysym.sym == SDLK_ESCAPE) {
            SDL_FreeSurface(menus[0]);
            SDL_FreeSurface(menus[1]);
            SDL_FreeSurface(screen);
            SDL_DestroyTexture(texture);
            m_loop = SDL_FALSE;
            return (0);
          }

        case SDL_MOUSEMOTION:x = m_ev.motion.x;
          y = m_ev.motion.y;
          for (int i = 0; i < num_menu; i += 1) {
            if (x >= pos[i].x && x <= pos[i].x + pos[i].w &&
                y >= pos[i].y && y <= pos[i].y + pos[i].h) {
              if (!selected[i]) {
                selected[i] = 1;
                SDL_FreeSurface(menus[i]);
                menus[i] = TTF_RenderText_Solid(m_window.getShrift(), menu_point[i], color[1]);
              }
            } else {
              if (selected[i]) {
                selected[i] = 0;
                SDL_FreeSurface(menus[i]);
                menus[i] = TTF_RenderText_Solid(m_window.getShrift(), menu_point[i], color[0]);
              }
            }
          }
          break;

        case SDL_MOUSEBUTTONDOWN:x = m_ev.button.x;
          y = m_ev.button.y;
          for (int i = 0; i < num_menu; i += 1) {
            if (x >= pos[i].x && x <= pos[i].x + pos[i].w &&
                y >= pos[i].y && y <= pos[i].y + pos[i].h) {
              SDL_FreeSurface(screen);
              SDL_DestroyTexture(texture);
              SDL_FreeSurface(menus[0]);
              SDL_FreeSurface(menus[1]);
              return (i + 1);
            }
          }
          break;
      }
    }

    for (int i = 0; i < num_menu; i += 1) {
      SDL_BlitSurface(menus[i], NULL, screen, &pos[i]);
    }

    texture = SDL_CreateTextureFromSurface(m_window.getRender(), screen);
    SDL_Rect rect;
    SDL_QueryTexture(texture, NULL, NULL, &rect.w, &rect.h);
    rect.x = (W - rect.w) / 2;
    rect.y = (H - rect.h) / 2;
    SDL_RenderClear(m_window.getRender());
    SDL_RenderCopy(m_window.getRender(), texture, NULL, &rect);
    SDL_RenderPresent(m_window.getRender());
  }
}

void Game::game_loop() {
  cout << "Game main_loop" << endl;
  SDL_Event event;

  static int lastTime = 0;
  while (m_loop) {
    lastFrame = SDL_GetTicks();
    if (lastFrame >= (lastTime + 1000)) {
      lastTime = lastFrame;
      fps = frameCount;
      frameCount = 0;
    }
    // Allow quiting with escape key by polling for pending events
    while (SDL_PollEvent(&event)) {
//    while (SDL_WaitEvent(&event)) {  // not working
      on_event(event);
    }
    if (!m_pause) {
      update();
    }
    render();
  }
  // clean
}

void Game::on_event(SDL_Event &event) {
  switch (event.type) {
    case SDL_QUIT:m_loop = SDL_FALSE;
      break;
    case SDL_KEYDOWN:
      if (event.key.keysym.sym == SDLK_ESCAPE) {
        m_loop = SDL_FALSE;
        break;
      }
      if (event.key.keysym.sym == SDLK_SPACE) {
        m_pause = !m_pause;
        break;
      }

      if (event.key.keysym.sym == SDLK_p) {  // new ball
        // new game
        m_ball->set_new_ball(1);
        m_ball->moving();
      }

      if (event.key.keysym.sym == SDLK_UP || event.key.keysym.sym == SDLK_DOWN ||
          event.key.keysym.sym == SDLK_RIGHT || event.key.keysym.sym == SDLK_LEFT) {
        m_player_left->set_move(event.key.keysym.sym);
      }
      if (m_number_pl == 2) {
        if (event.key.keysym.sym == SDLK_w || event.key.keysym.sym == SDLK_s ||
            event.key.keysym.sym == SDLK_d || event.key.keysym.sym == SDLK_a) {
          m_player_right->set_move(event.key.keysym.sym);
        }
      }
      break;
    case SDL_KEYUP:
      if (event.key.keysym.sym == SDLK_UP || event.key.keysym.sym == SDLK_DOWN ||
          event.key.keysym.sym == SDLK_RIGHT || event.key.keysym.sym == SDLK_LEFT) {
          m_player_left->disable_move(event.key.keysym.sym);
      }
      if (m_number_pl == 2) {
        if (event.key.keysym.sym == SDLK_w || event.key.keysym.sym == SDLK_s ||
            event.key.keysym.sym == SDLK_d || event.key.keysym.sym == SDLK_a) {
          m_player_right->disable_move(event.key.keysym.sym);
        }
      }
      break;
    default:m_loop = SDL_TRUE;
  }
}

void Game::update() {
  m_player_left->moving();
  if (m_number_pl == 2)
    m_player_right->moving();
  else {
//    m_player_right->set_move(m_ball->center.y);
//    m_player_right->disable_move(m_ball->center.x);
    m_player_right_bot2->move_bot(m_ball->center.x, m_ball->center.y);
  }
  m_ball->moving();

  if (check_goal()) {
    m_player_left->move_start();
    m_player_right_bot2->move_start();
  }
  colision(m_player_left);
  colision2(m_player_right_bot2);
}

void Game::render() {
  SDL_RenderClear(m_window.getRender());

  frameCount++;
  int timerFPS = SDL_GetTicks() - lastFrame;
  if(timerFPS < (1000 / 60)) {
    SDL_Delay((1000 / 60) - timerFPS);
  }

  // Blank out the renderer with all black
  SDL_SetRenderDrawColor(m_window.getRender(), 0, 0, 0, 0);
  SDL_RenderClear(m_window.getRender());

  // Note that all render copys are order specific.

  SDL_RenderCopy(m_window.getRender(), m_window.getTexture(), NULL, NULL);

  // Render the sample rectangle
  SDL_SetRenderDrawColor(m_window.getRender(), 255, 255, 255, 1);
  SDL_RenderFillRect(m_window.getRender(), m_player_left->get_rect());
  SDL_RenderFillRect(m_window.getRender(), m_player_right_bot2->get_rect());
  SDL_SetRenderDrawColor(m_window.getRender(), 255, 255, 0, 1);
  SDL_RenderFillRect(m_window.getRender(), m_ball->get_rect());
  // Render sample text
//  SDL_RenderCopy(m_window.getRender(), _headerText, NULL, &_headerTextRect);

  draw_score(W / 2 + FONT_SIZE, FONT_SIZE * 2);
  // Present to renderer
  SDL_RenderPresent(m_window.getRender());
//  SDL_Delay(10);
}



void Game::Exit() {
}

void Game::draw_score(int x, int y) {
  std::string text = "Score ";
  text += std::to_string(m_game_play->get_score().left);
  text +=  " : ";
  text += std::to_string(m_game_play->get_score().right);
  m_score_surface = TTF_RenderText_Solid(m_window.getShrift(), text.c_str(), m_text_color);
  m_score_texture = SDL_CreateTextureFromSurface(m_window.getRender(), m_score_surface);
  m_score_board.w = m_score_surface->w;
  m_score_board.h = m_score_surface->h;
  m_score_board.x = x - m_score_board.w;
  m_score_board.y = y - m_score_board.h;
  SDL_RenderCopy(m_window.getRender(), m_score_texture, NULL, &m_score_board);
  m_score_texture = NULL;
}

void Game::colision(std::shared_ptr<Player> player) {


  double Dx = m_ball->get_center().x - player->get_center().x;
  double Dy = m_ball->get_center().y - player->get_center().y;
  double d = sqrt(Dx * Dx + Dy * Dy);

  if (d == 0)
    d = 0.01;

  if (d <= m_ball->get_radius() + player->get_radius()) {
    double cos_a = Dx / d;
    double sin_a = Dy / d;
    double Vn1 = player->get_speed().x * cos_a + player->get_speed().y * sin_a;
    double Vn2 = m_ball->get_speed().x * cos_a + m_ball->get_speed().y * sin_a;

    // проверка на наложение
    double dt = (m_ball->get_radius() + player->get_radius() - d) / (Vn1 - Vn2);
    if (dt > 0.6)
      dt = 0.6;
    else if (dt < -0.6)
      dt = -0.6;

    //временный сдвиг
    player->get_rect()->x -= player->get_speed().x * dt;
    player->get_rect()->y -= player->get_speed().y * dt;
    player->set_center();


    m_ball->pos.x -= m_ball->speed.x * dt;
    m_ball->pos.y -= m_ball->speed.y * dt;
//    m_ball.set_center();

    //перерасчет
    Dx = m_ball->center.x - player->get_center().x;
    Dy = m_ball->center.y - player->get_center().y;
    d = sqrt(Dx * Dx + Dy * Dy);

    if (d == 0)
      d = 0.01;

    cos_a = Dx / d;
    sin_a = Dy / d;

    Vn1 = player->get_speed().x * cos_a + player->get_speed().y * sin_a;
    Vn2 = m_ball->speed.x * cos_a + m_ball->speed.y * sin_a;

    double Vt2 = -m_ball->speed.x * sin_a + m_ball->speed.y * cos_a;

    //проверка направления ускорения
    if (Vn2 < 0)
      Vn2 = Vn1 - Vn2;
    else
      Vn2 += Vn1;

    m_ball->speed.x = Vn2 * cos_a - Vt2 * sin_a;
    m_ball->speed.y = Vn2 * sin_a + Vt2 * cos_a;

    //обратный сдвиг
    player->get_rect()->x += player->get_speed().x * dt;
    player->get_rect()->y += player->get_speed().y * dt;
    player->set_center();

    if (m_ball->speed.x > 50)
      m_ball->speed.x = 50;
    if (m_ball->speed.x < -50)
      m_ball->speed.x = -50;
    if (m_ball->speed.y > 50)
      m_ball->speed.y = 50;
    if (m_ball->speed.y < -50)
      m_ball->speed.y = -50;

    m_ball->pos.x += m_ball->speed.x * dt;
    m_ball->pos.y += m_ball->speed.y * dt;
    m_ball->set_center();

//    if (!Mix_PlayingMusic())
//      Mix_PlayMusic(window.bum, 0);

  }

}

bool Game::check_goal()
{
//  cout << " check_goal" << endl;

  if (m_ball->pos.x  + PLAYER_W >= W) {
    m_game_play->add_score(0);
    GamePlayController::Score res = m_game_play->get_score();
    cout << "player left score =" << res.left << " : " << res.right << endl;
    return (true);
  }
  else if (m_ball->pos.x <= 0 ) {
    m_game_play->add_score(1);
    GamePlayController::Score res = m_game_play->get_score();
    cout << "player right score = " << res.left << " : " << res.right << endl;
    return (true);
  }
  return (false);
}
void Game::colision2(std::shared_ptr<Bot> player) {
  double Dx = m_ball->get_center().x - player->get_center().x;
  double Dy = m_ball->get_center().y - player->get_center().y;
  double d = sqrt(Dx * Dx + Dy * Dy);

  if (d == 0)
    d = 0.01;

  if (d <= m_ball->get_radius() + player->get_radius()) {
    double cos_a = Dx / d;
    double sin_a = Dy / d;
    double Vn1 = player->get_speed().x * cos_a + player->get_speed().y * sin_a;
    double Vn2 = m_ball->get_speed().x * cos_a + m_ball->get_speed().y * sin_a;

    // проверка на наложение
    double dt = (m_ball->get_radius() + player->get_radius() - d) / (Vn1 - Vn2);
    if (dt > 0.6)
      dt = 0.6;
    else if (dt < -0.6)
      dt = -0.6;

    //временный сдвиг
    player->get_rect()->x -= player->get_speed().x * dt;
    player->get_rect()->y -= player->get_speed().y * dt;
    player->set_center();


    m_ball->pos.x -= m_ball->speed.x * dt;
    m_ball->pos.y -= m_ball->speed.y * dt;
//    m_ball.set_center();

    //перерасчет
    Dx = m_ball->center.x - player->get_center().x;
    Dy = m_ball->center.y - player->get_center().y;
    d = sqrt(Dx * Dx + Dy * Dy);

    if (d == 0)
      d = 0.01;

    cos_a = Dx / d;
    sin_a = Dy / d;

    Vn1 = player->get_speed().x * cos_a + player->get_speed().y * sin_a;
    Vn2 = m_ball->speed.x * cos_a + m_ball->speed.y * sin_a;

    double Vt2 = -m_ball->speed.x * sin_a + m_ball->speed.y * cos_a;

    //проверка направления ускорения
    if (Vn2 < 0)
      Vn2 = Vn1 - Vn2;
    else
      Vn2 += Vn1;

    m_ball->speed.x = Vn2 * cos_a - Vt2 * sin_a;
    m_ball->speed.y = Vn2 * sin_a + Vt2 * cos_a;

    //обратный сдвиг
    player->get_rect()->x += player->get_speed().x * dt;
    player->get_rect()->y += player->get_speed().y * dt;
    player->set_center();

    if (m_ball->speed.x > 50)
      m_ball->speed.x = 50;
    if (m_ball->speed.x < -50)
      m_ball->speed.x = -50;
    if (m_ball->speed.y > 50)
      m_ball->speed.y = 50;
    if (m_ball->speed.y < -50)
      m_ball->speed.y = -50;

    m_ball->pos.x += m_ball->speed.x * dt;
    m_ball->pos.y += m_ball->speed.y * dt;
    m_ball->set_center();

//    if (!Mix_PlayingMusic())
//      Mix_PlayMusic(window.bum, 0);

  }
}




