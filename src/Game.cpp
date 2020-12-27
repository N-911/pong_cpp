#include "Game.h"
#include <iostream>

using std::cout;
using std::endl;

Game::Game() {
  cout << "Game Constructor" << endl;
  m_run = true;
  m_loop = SDL_TRUE;
  m_number_pl = 2;

//  m_number_pl = show_menu();
  m_text_color = (SDL_Color) {255, 255, 0, 255};
  m_player_left = std::shared_ptr<Player>(new Player(0));
  m_player_right = std::shared_ptr<Player>(new Player(1));
  m_ball  = std::shared_ptr<Ball>(new Ball(1));
}

Game::~Game() {
  cout << "Game Destructor" << endl;
  SDL_DestroyTexture(m_text_texture[0]);
  SDL_DestroyTexture(m_text_texture[1]);
  SDL_FreeSurface(m_text_surface[0]);
  SDL_FreeSurface(m_text_surface[1]);
}

void Game::main_loop() {
  cout << "Game main_loop" << endl;
  SDL_Event event;

  while (m_loop) {
    // Allow quiting with escape key by polling for pending events
    while (SDL_PollEvent(&event)) {
//    while (SDL_WaitEvent(&event)) {  // not working
      on_event(event);
    }
      m_player_left->moving();
      m_player_right->moving();
      m_ball->moving();
      colision(m_player_left);
      colision(m_player_right);
      draw();
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
      if (event.key.keysym.sym == SDLK_p) {
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

int Game::show_menu() {
  SDL_Surface *screen = SDL_CreateRGBSurface(0, WIDTH, HEIGHT, 32, 0, 0, 0, 0);
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
        case SDL_QUIT:SDL_FreeSurface(menus[0]);
          SDL_FreeSurface(menus[1]);
          SDL_FreeSurface(screen);
          SDL_DestroyTexture(texture);
          m_run = false;
          return (0);

        case SDL_KEYDOWN:
          if (m_ev.key.keysym.sym == SDLK_ESCAPE) {
            SDL_FreeSurface(menus[0]);
            SDL_FreeSurface(menus[1]);
            SDL_FreeSurface(screen);
            SDL_DestroyTexture(texture);
            m_run = false;
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
    rect.x = (WIDTH - rect.w) / 2;
    rect.y = (HEIGHT - rect.h) / 2;

    SDL_RenderClear(m_window.getRender());
    SDL_RenderCopy(m_window.getRender(), texture, NULL, &rect);
    SDL_RenderPresent(m_window.getRender());
  }
}

void Game::draw() {
  SDL_RenderClear(m_window.getRender());

  // Blank out the renderer with all black
  SDL_SetRenderDrawColor(m_window.getRender(), 0, 0, 0, 0);
  SDL_RenderClear(m_window.getRender());

  // Note that all render copys are order specific.

  // Render the sample texture. We could use a source and/or destination rect to render to
  // but for now we'll just use it as a background

  SDL_RenderCopy(m_window.getRender(), m_window.getTexture(), NULL, NULL);

  // Render the sample rectangle
  SDL_SetRenderDrawColor(m_window.getRender(), 255, 255, 255, 1);
  SDL_RenderFillRect(m_window.getRender(), m_player_left->get_rect());
  SDL_RenderFillRect(m_window.getRender(), m_player_right->get_rect());
  SDL_SetRenderDrawColor(m_window.getRender(), 255, 255, 0, 1);
  SDL_RenderFillRect(m_window.getRender(), m_ball->get_rect());
  // Render sample text
//  SDL_RenderCopy(m_window.getRender(), _headerText, NULL, &_headerTextRect);

  // Present to renderer
  SDL_RenderPresent(m_window.getRender());
  SDL_Delay(10);


//  play_mus = check_goal();
//  if (play_mus) {
  // play music
//    Mix_PlayMusic(m_window.m_goal, 0);
//  }

//  SDL_Rect rect;
//  rect.x = 0;
//  rect.y = 0;
//  rect.w = 15;
//  rect.h = 50;
//  m_window.draw_surface(m_color);

//  SDL_SetRenderDrawColor(m_window.getRender(), 255, 255, 255, 1);
//  SDL_RenderFillRect(m_window.getRender(), &rect);
//  m_player1->draw_surface(m_color);
//  m_player1->moving();

  /*
  m_player2->draw_surface(m_color);
  if (NUM_PLAYERS == 2)
  {
    player2->moving();
  }
  else
  {
    player2->set_move(puck.center.x);
    player2->disable_move(puck.center.y);
    player2->moving();
  }

  m_ball.draw_surface(m_color);
  m_ball.moving(m_window.bum);

  colision(player);
  colision(player2);


  SDL_UpdateTexture(window.texture, NULL, m_color, WIDTH << 2);
  SDL_RenderCopy(window.render, window.texture, NULL, NULL);
  draw_score();
  SDL_RenderPresent(window.render);

  if (play_mus) {
    while (Mix_PlayingMusic());
  }

  */
}

void Game::events() {
  while (SDL_PollEvent(&m_ev)) {
    switch (m_ev.type) {
      case SDL_QUIT:m_run = false;
        break;

      case SDL_KEYDOWN:
        if (m_ev.key.keysym.sym == SDLK_ESCAPE) {
          m_run = false;
        }
        if (m_ev.key.keysym.sym == SDLK_UP || m_ev.key.keysym.sym == SDLK_DOWN ||
            m_ev.key.keysym.sym == SDLK_RIGHT || m_ev.key.keysym.sym == SDLK_LEFT) {
          m_player_left->set_move(m_ev.key.keysym.sym);
        }
        if (m_number_pl == 2) {
          if (m_ev.key.keysym.sym == SDLK_w || m_ev.key.keysym.sym == SDLK_s ||
              m_ev.key.keysym.sym == SDLK_d || m_ev.key.keysym.sym == SDLK_a) {
            m_player_right->set_move(m_ev.key.keysym.sym);
          }
        }
        break;

      case SDL_KEYUP:
        if (m_ev.key.keysym.sym == SDLK_UP || m_ev.key.keysym.sym == SDLK_DOWN ||
            m_ev.key.keysym.sym == SDLK_RIGHT || m_ev.key.keysym.sym == SDLK_LEFT) {
          m_player_left->disable_move(m_ev.key.keysym.sym);
        }
        if (m_number_pl == 2) {
          if (m_ev.key.keysym.sym == SDLK_w || m_ev.key.keysym.sym == SDLK_s ||
              m_ev.key.keysym.sym == SDLK_d || m_ev.key.keysym.sym == SDLK_a) {
            m_player_right->disable_move(m_ev.key.keysym.sym);
          }
        }
        break;
    }
  }
}
bool Game::check_goal() const {
  return false;
}
void Game::Exit() {
  m_run = false;
}
void Game::draw_score() {

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

    /* проверка на наложение */
    double dt = (m_ball->get_radius() + player->get_radius() - d) / (Vn1 - Vn2);
    if (dt > 0.6)
      dt = 0.6;
    else if (dt < -0.6)
      dt = -0.6;

    /*временный сдвиг*/
    player->pos.x -= player->speed.x * dt;
    player->pos.y -= player->speed.y * dt;
//    player->set_center();


    m_ball->pos.x -= m_ball->speed.x * dt;
    m_ball->pos.y -= m_ball->speed.y * dt;
//    m_ball.set_center();

    /*перерасчет*/
    Dx = m_ball->center.x - player->center.x;
    Dy = m_ball->center.y - player->center.y;
    d = sqrt(Dx * Dx + Dy * Dy);

    if (d == 0)
      d = 0.01;

    cos_a = Dx / d;
    sin_a = Dy / d;

    Vn1 = player->speed.x * cos_a + player->speed.y * sin_a;
    Vn2 = m_ball->speed.x * cos_a + m_ball->speed.y * sin_a;

    double Vt2 = -m_ball->speed.x * sin_a + m_ball->speed.y * cos_a;

    /*проверка направления ускорения*/
    if (Vn2 < 0)
      Vn2 = Vn1 - Vn2;
    else
      Vn2 += Vn1;

    m_ball->speed.x = Vn2 * cos_a - Vt2 * sin_a;
    m_ball->speed.y = Vn2 * sin_a + Vt2 * cos_a;

    /*обратный сдвиг*/
    player->pos.x += player->speed.x * dt;
    player->pos.y += player->speed.y * dt;
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

/*
 *
  m_text_surface[0] = TTF_RenderText_Solid(m_window.getShrift(), "Player 1", m_text_color);

  if (m_number_pl == 2) {
    m_player2 = std::shared_ptr<Player>(new Player(POSITION::LEFT));
    m_text_surface[1] = TTF_RenderText_Solid(m_window.getShrift(), "Player 2", m_text_color);

  } else {
//    m_player2 = std::shared_ptr<Player>(new Player(POSITION::UP));
    m_text_surface[1] = TTF_RenderText_Solid(m_window.getShrift(), "Bot", m_text_color);
  }

  m_text_texture[0] = SDL_CreateTextureFromSurface(m_window.getRender(), m_text_surface[0]);
  m_text_texture[1] = SDL_CreateTextureFromSurface(m_window.getRender(), m_text_surface[1]);
 */

/*
void Game::handle_mouse_drag(SDL_Event e) {
  if (e.type == SDL_MOUSEBUTTONDOWN) {
    // Point where mouse button down occurs
    SDL_Point p = {.x = e.motion.x, .y = e.motion.y};

    if (SDL_PointInRect(&p, &m_sampleRect)) {
      _inSampleRect = SDL_TRUE;
    }
  }

  if (e.type == SDL_MOUSEBUTTONUP && _inSampleRect == SDL_TRUE) {
    _inSampleRect = SDL_FALSE;
  }

  if (e.type == SDL_MOUSEMOTION && _inSampleRect == SDL_TRUE) {
    m_sampleRect.x += e.motion.xrel;
    m_sampleRect.y += e.motion.yrel;
  }
}
*/