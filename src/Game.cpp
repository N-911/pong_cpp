#include "Game.h"
#include <iostream>
#include <memory>

#include "IEventManager.h"

using std::cout;
using std::endl;

Game::Game()
{
    cout << "Game Constructor" << endl;
    m_loop = SDL_TRUE;
    m_number_pl = 2;
    m_game_play = new GamePlayController();

    m_frame_count = 0;
    m_last_frame = 0;

//    m_number_pl = show_menu();
    m_text_color.r = 255;
    m_text_color.g = 255;
    m_text_color.b = 0;
    m_text_color.a = 255;

    m_score_board.w = 100;
    m_score_board.h = FONT_SIZE;
    m_score_board.x = SCORE_BOURD_X - m_score_board.w;
    m_score_board.y = SCORE_BOURD_Y - m_score_board.h;

    m_event_manager = new EventManager();
    m_ball = std::unique_ptr<Ball>(new Ball(W / 2, H / 2));
    m_left = std::unique_ptr<Player>(new Player());

    if (m_number_pl == 1) {
//        m_right = std::unique_ptr<Bot>(new Bot());
    }
    else {
        m_right = std::unique_ptr<Player>(new Player());  //Player
    }
    m_pause = false;
}

Game::~Game()
{
    cout << "Game Destructor" << endl;
    delete m_game_play;
//  delete m_player_left;
//  delete m_current_player_right;
}

int Game::show_menu()
{
    SDL_Surface* screen = SDL_CreateRGBSurface(0, W, H, 32, 0, 0, 0, 0);
    SDL_Texture* texture;

    int x, y;
    const int num_menu = 2;
    const char* menu_point[num_menu] = {"Single Player", "Multiplayer"};

    bool selected[num_menu] = {0, 0};
    SDL_Color color[2] = {{255, 255, 255, 0}, {255, 0, 0, 0}};

    SDL_Surface* menus[num_menu];

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
                    }
                    else {
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

void Game::game_loop()
{
    SDL_Event event;

    /*
    const int TICKS_PER_SECOND = 60;
    const int SKIP_TICKS = 1000 / TICKS_PER_SECOND;
    const int MAX_FRAMESKIP = 10;

    unsigned int next_game_tick = SDL_GetTicks();
    int loops;
    float interpolation;

  //  Постоянная скорость игры, независящая от переменного FPS
    while (m_loop) {
      loops = 0;
      while (SDL_GetTicks() > next_game_tick && loops < MAX_FRAMESKIP) {
        while (SDL_PollEvent(&event)) {
          on_event(event);
        }
        if (!m_pause) {
          update();
        }
        next_game_tick += SKIP_TICKS;
        loops++;
      }
      interpolation = float(SDL_GetTicks() + SKIP_TICKS - next_game_tick)
          / float(SKIP_TICKS);
      cout << "interpolation =" << interpolation << endl;
      render(interpolation);
    }
    */

    static int lastTime = 0;
    while (m_loop) {
        m_last_frame = SDL_GetTicks();  // number of milliseconds since the SDL library initialized
        if (m_last_frame >= (lastTime + 1000)) {
            lastTime = m_last_frame;
            m_fps = m_frame_count;
            m_frame_count = 0;
        }
        cout << "fps =" << m_fps << endl;

        while (SDL_PollEvent(&event)) {
            on_event(event);
        }
        if (!m_pause) {
            update();
        }
        render(1.0);
    }

}

void Game::on_event(SDL_Event& event)
{
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

        if (event.key.keysym.sym == SDLK_p) {  // new ball for testing
//        m_ball->set_new_ball(1);
//        m_ball->moving();
        }
        if (event.key.keysym.sym == SDLK_UP || event.key.keysym.sym == SDLK_DOWN ||
                event.key.keysym.sym == SDLK_RIGHT || event.key.keysym.sym == SDLK_LEFT) {
            m_left->set_move(event.key.keysym.sym);
        }
        if (m_number_pl == 2) {
            if (event.key.keysym.sym == SDLK_w || event.key.keysym.sym == SDLK_s ||
                    event.key.keysym.sym == SDLK_d || event.key.keysym.sym == SDLK_a) {
                m_right->set_move(event.key.keysym.sym);
            }
        }
        break;
    case SDL_KEYUP:
        if (event.key.keysym.sym == SDLK_UP || event.key.keysym.sym == SDLK_DOWN ||
                event.key.keysym.sym == SDLK_RIGHT || event.key.keysym.sym == SDLK_LEFT) {
            m_left->disable_move(event.key.keysym.sym);
        }
        if (m_number_pl == 2) {
            if (event.key.keysym.sym == SDLK_w || event.key.keysym.sym == SDLK_s ||
                    event.key.keysym.sym == SDLK_d || event.key.keysym.sym == SDLK_a) {
                m_right->disable_move(event.key.keysym.sym);
            }
        }
        break;
    default:m_loop = SDL_TRUE;
    }
}

void Game::update()
{
    m_left->moving();
//  if (m_number_pl == 2)
//    m_right->moving();
//  else
    m_right->moving();
    m_ball->moving();

    // reset all position
    if (int win_side = check_goal(); win_side != -1) {
//    m_left->move_start();
//    m_right->move_start();
//    m_ball->set_new_ball(win_side);
    }
    else {
//    m_left->check_colision(m_ball);
//    m_right->check_colision(m_ball);
    }
}

void Game::render(float interpolation)
{
    SDL_RenderClear(m_window.getRender());

    m_frame_count++;
    int timerFPS = SDL_GetTicks() - m_last_frame;
    if (timerFPS < (1000 / 60)) {
        SDL_Delay((1000 / 60) - timerFPS);
    }

    // Интерполяция и предсказание смещение шарика
//  view_position = position + (speed * interpolation)

//  int ball_view_position_x = m_ball->get_rect()->x + (m_ball->get_speed().x * interpolation);
//  int ball_view_position_y = m_ball->get_rect()->y + (m_ball->get_speed().y * interpolation);
//  m_ball->set_rect_x(ball_view_position_x);
//  m_ball->set_rect_y(ball_view_position_y);

    SDL_SetRenderDrawColor(m_window.getRender(), 0, 0, 0, 0);
    SDL_RenderClear(m_window.getRender());
    SDL_RenderCopy(m_window.getRender(), m_window.getTexture(), NULL, NULL);
    SDL_SetRenderDrawColor(m_window.getRender(), 255, 255, 255, 1);
    SDL_RenderFillRect(m_window.getRender(), m_left->get_rect());
    SDL_RenderFillRect(m_window.getRender(), m_right->get_rect());
    SDL_SetRenderDrawColor(m_window.getRender(), 255, 0, 0, 1);
//  SDL_RenderFillRect(m_window.getRender(), m_ball->get_rect());
//  draw_score();
    SDL_RenderPresent(m_window.getRender());
}

void Game::draw_score()
{
    std::string text = "Score ";
    text += std::to_string(m_game_play->get_score()[0]);
    text += " : ";
    text += std::to_string(m_game_play->get_score()[1]);
    m_score_surface = TTF_RenderText_Solid(m_window.getShrift(), text.c_str(), m_text_color);
    m_score_texture = SDL_CreateTextureFromSurface(m_window.getRender(), m_score_surface);
    SDL_RenderCopy(m_window.getRender(), m_score_texture, NULL, &m_score_board);
    SDL_DestroyTexture(m_score_texture);
    SDL_FreeSurface(m_score_surface);
}

/*return  0 left side goal, 1 - right side goal, -1 - no goal */

int Game::check_goal()
{

    /*
    if (m_ball->get_rect()->x + BALL_SIZE >= W) {
      m_game_play->add_score(0);
      GamePlayController::Score res = m_game_play->get_score();
      cout << "player left goal score =" << res.left << " : " << res.right << endl;
      return 1;
    } else if (m_ball->get_rect()->x <= 0) {
      m_game_play->add_score(1);
      std::vector<int> res = m_game_play->get_score();
      cout << "player right goal score = " << res[0] << " : " << res[1] << endl;
      return 0;
    }
     */
    return -1;
}
