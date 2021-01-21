#include "Game.h"
#include <iostream>
#include <iomanip>
#include <memory>

#include "IEventManager.h"

using std::cout;
using std::endl;

void print_FPS(uint32_t time_since_start, int frames);

Game::Game()
{
    cout << "Game Constructor" << endl;
    m_loop = SDL_TRUE;
    m_number_pl = 2;
    m_game_play = std::unique_ptr<GamePlayController>(new GamePlayController());

    GameState m_state(GameState::MainMenu);
    m_frame_count = 0;
    m_last_frame = 0;
    m_state = GameState::GameScreen;

//    m_number_pl = show_menu();
    m_text_color.r = 255;
    m_text_color.g = 255;
    m_text_color.b = 0;
    m_text_color.a = 255;

    m_score_board.w = 100;
    m_score_board.h = FONT_SIZE;
    m_score_board.x = SCORE_BOURD_X - m_score_board.w;
    m_score_board.y = SCORE_BOURD_Y - m_score_board.h;

    m_event_manager = std::shared_ptr<EventManager>(new EventManager());

    m_window = new Window(*m_event_manager);

    m_ball = std::make_unique<Ball>(W / 2, H / 2);
    m_game_obj.push_back(std::make_unique<Player>(*m_event_manager, 0));

    m_timeAtLaunch = SDL_GetTicks();

    if (m_number_pl == 1) {
        m_game_obj.push_back(std::make_unique<Bot>(1));
    }
    else {
        m_game_obj.push_back(std::make_unique<Player>(*m_event_manager, 1));
    }
    m_pause = false;
}

Game::~Game()
{
    cout << "Game Destructor" << endl;
}

void Game::game_loop()
{
    SDL_Event event;
    static int lastTime = 0;
    while (m_loop) {
        int t1 = SDL_GetTicks();

        m_last_frame = SDL_GetTicks();  // number of milliseconds since the SDL library initialized
        if (m_last_frame >= (lastTime + 1000)) {
            lastTime = m_last_frame;
            m_fps = m_frame_count;
            m_frame_count = 0;
        }
        cout << "fps =" << m_fps << endl;
        while (SDL_PollEvent(&event)) {
            switch (m_state) {
                case (GameState::MainMenu): {
                    if (event.type == SDL_QUIT) {
                        cout << " press quit" << endl;
                        m_loop = SDL_FALSE;
                        break;
                    }
                }
                case (GameState::GameScreen): {
                    if (event.type == SDL_KEYDOWN) {
                        if (event.key.keysym.sym == SDLK_ESCAPE) {
                            m_loop = SDL_FALSE;
                            break;
                        }
                        if (event.key.keysym.sym == SDLK_SPACE) {
                            m_pause = !m_pause;
                            cout << "m_pause =" << std::boolalpha << m_pause << endl;
                            break;
                        }
                    }
                    if (m_pause == SDL_FALSE) {
                        m_event_manager->ChangeStatus(event);
                        break;
                    }
                }
                default:break;
            }
        }
        if (!m_pause)
            update();
        render_scene();
        // Delay to keep FPS consistent
        int t2 = SDL_GetTicks() - t1;
        int ticks_per_frame = 1000 / 60;
        if (t2 < ticks_per_frame) SDL_Delay(ticks_per_frame - t2);
        print_FPS(m_timeAtLaunch, m_frames);
    }
}

Vec2i Game::ball_collision_with_player(int i, Vec2i col)
{
    int platform_left;
    int platform_right;
    int platform_top;
    int platform_bottom;

    int rectCenterX;
    int rectCenterY;

    // Move ball back one step
    int prew_x_ball = m_ball->get_ball_geomerty().x - m_ball->velocity().x;
    int prew_y_ball = m_ball->get_ball_geomerty().y - m_ball->velocity().y;

    m_ball->set_x(prew_x_ball);
    m_ball->set_y(prew_y_ball);

    platform_left = m_game_obj[i]->get_rect()->x;
    platform_right = m_game_obj[i]->get_rect()->x + PLAYER_W;
    platform_top = m_game_obj[i]->get_rect()->y;
    platform_bottom = m_game_obj[i]->get_rect()->y + PLAYER_H;

    rectCenterX = (platform_left + platform_right) / 2;
    rectCenterY = (platform_bottom + platform_top) / 2;

    int diff_x = col.x - rectCenterX;
    int diff_y = col.y - rectCenterY;
    int y_magnitude = abs(diff_y / diff_x);

    int y_dir_ball = m_ball->velocity().y < 0 ? -1 : 1;

    int direction_multiplier_y = 1;

    if (col.y - m_ball->velocity().y >= platform_bottom || col.y - m_ball->velocity().y <= platform_top)
        direction_multiplier_y = -1;    // check if bottom or top of platform was hit

    // Calculate new y velocity
    int velocity_y = y_magnitude * y_dir_ball * direction_multiplier_y;

    // Calculate new x velocity
    int velocity_x = m_ball->velocity().x * -1;
    return {velocity_x, velocity_y};

}

void Game::update()
{
    int winner;
    m_ball->move();
    winner = m_game_play->ball_collision(m_ball->get_rect()->x, m_ball->get_rect()->y);
    if (winner != -1) {
//        cout << "new ball" << endl;
        m_ball->set_new_ball(winner);
    }
    Vec2i colis_point;

    for (int i = 0; i < 2; ++i) {
        colis_point = m_game_obj[i]->check_colision(m_ball->get_ball_geomerty());
        if (colis_point.x != -1 && colis_point.y != -1) {
            cout << "detect colision x = " << colis_point.x << " y = " << colis_point.y << endl;
            m_ball->set_velocity(ball_collision_with_player(i, colis_point));
            cout << "ball  x = " << m_ball->get_ball_geomerty().x << " y = " << m_ball->get_ball_geomerty().y << endl;
        }
    }
}

void Game::render_scene()
{
    SDL_RenderClear(m_window->get_render());

//    m_frame_count++;
//    int timerFPS = SDL_GetTicks() - m_last_frame;
//    if (timerFPS < (1000 / 60)) {
//        SDL_Delay((1000 / 60) - timerFPS);
//    }

    switch (m_state) {
        case (GameState::MainMenu): {
        }
        case (GameState::GameScreen) : {

//            cout << "Game Screen" << endl;

            SDL_SetRenderDrawColor(m_window->get_render(), 0, 0, 0, 0);
            SDL_RenderClear(m_window->get_render());
            SDL_RenderCopy(m_window->get_render(), m_window->get_texture("background"), NULL, NULL);
            SDL_SetRenderDrawColor(m_window->get_render(), 255, 255, 255, 1);

//            cout << "m_left x =" << m_left->get_rect()->x << "m_left x=" << m_left->get_rect()->x << endl;
//            cout << "m_left y =" << m_left->get_rect()->x << "m_left y=" << m_left->get_rect()->y << endl;

            SDL_RenderFillRect(m_window->get_render(), m_game_obj[0]->get_rect());
            SDL_SetRenderDrawColor(m_window->get_render(), 255, 255, 0, 255);
            SDL_RenderFillRect(m_window->get_render(), m_game_obj[1]->get_rect());
            SDL_SetRenderDrawColor(m_window->get_render(), 255, 0, 1, 1);


//            SDL_Rect newPos = { m_ball->get_rect()->x, m_ball->get_rect()->y, _boundingBox.r*2, _boundingBox.r*2 };
//            SDL_RenderCopy(renderer, _texture, NULL, &newPos);


            SDL_RenderCopy(m_window->get_render(), m_window->get_texture("ball"), NULL,
                    m_ball->get_rect());

            draw_score();
            SDL_RenderPresent(m_window->get_render());
        }
        default: break;
    }
    m_frames++;
}

void Game::render(float interpolation)
{
    SDL_RenderClear(m_window->get_render());

//    m_frame_count++;
//    int timerFPS = SDL_GetTicks() - m_last_frame;
//    if (timerFPS < (1000 / 60)) {
//        SDL_Delay((1000 / 60) - timerFPS);
//    }

    // Интерполяция и предсказание смещение шарика
//  view_position = position + (speed * interpolation)

//  int ball_view_position_x = m_ball->get_rect()->x + (m_ball->get_speed().x * interpolation);
//  int ball_view_position_y = m_ball->get_rect()->y + (m_ball->get_speed().y * interpolation);
//  m_ball->set_rect_x(ball_view_position_x);
//  m_ball->set_rect_y(ball_view_position_y);

    SDL_SetRenderDrawColor(m_window->get_render(), 0, 0, 0, 0);
    SDL_RenderClear(m_window->get_render());
    SDL_RenderCopy(m_window->get_render(), m_window->get_texture(std::string()), NULL, NULL);
    SDL_SetRenderDrawColor(m_window->get_render(), 255, 255, 255, 1);
//    SDL_RenderFillRect(m_window->get_render(), m_left->get_rect());
//    SDL_RenderFillRect(m_window->get_render(), m_right->get_rect());
    SDL_SetRenderDrawColor(m_window->get_render(), 255, 0, 0, 1);
//  SDL_RenderFillRect(m_window.getRender(), m_ball->get_rect());
//  draw_score();
    SDL_RenderPresent(m_window->get_render());
}

void Game::draw_score()
{
    std::string text = "Score ";
    text += std::to_string(m_game_play->get_score()[0]);
    text += " : ";
    text += std::to_string(m_game_play->get_score()[1]);
    m_score_surface = TTF_RenderText_Solid(m_window->get_shrift(), text.c_str(), m_text_color);
    m_score_texture = SDL_CreateTextureFromSurface(m_window->get_render(), m_score_surface);
    SDL_RenderCopy(m_window->get_render(), m_score_texture, NULL, &m_score_board);
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
//                m_left->set_move(event.key.keysym.sym);
            }
            if (m_number_pl == 2) {
                if (event.key.keysym.sym == SDLK_w || event.key.keysym.sym == SDLK_s ||
                        event.key.keysym.sym == SDLK_d || event.key.keysym.sym == SDLK_a) {
//                    m_right->set_move(event.key.keysym.sym);
                }
            }
            break;
        case SDL_KEYUP:
            if (event.key.keysym.sym == SDLK_UP || event.key.keysym.sym == SDLK_DOWN ||
                    event.key.keysym.sym == SDLK_RIGHT || event.key.keysym.sym == SDLK_LEFT) {
//                m_left->disable_move(event.key.keysym.sym);
            }
            if (m_number_pl == 2) {
                if (event.key.keysym.sym == SDLK_w || event.key.keysym.sym == SDLK_s ||
                        event.key.keysym.sym == SDLK_d || event.key.keysym.sym == SDLK_a) {
//                    m_right->disable_move(event.key.keysym.sym);
                }
            }
            break;
        default:m_loop = SDL_TRUE;
    }
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

    menus[0] = TTF_RenderText_Solid(m_window->get_shrift(), menu_point[0], color[0]);
    menus[1] = TTF_RenderText_Solid(m_window->get_shrift(), menu_point[1], color[0]);

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
                                menus[i] = TTF_RenderText_Solid(m_window->get_shrift(), menu_point[i], color[1]);
                            }
                        }
                        else {
                            if (selected[i]) {
                                selected[i] = 0;
                                SDL_FreeSurface(menus[i]);
                                menus[i] = TTF_RenderText_Solid(m_window->get_shrift(), menu_point[i], color[0]);

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

        texture = SDL_CreateTextureFromSurface(m_window->get_render(), screen);
        SDL_Rect rect;
        SDL_QueryTexture(texture, NULL, NULL, &rect.w, &rect.h);
        rect.x = (W - rect.w) / 2;
        rect.y = (H - rect.h) / 2;
        SDL_RenderClear(m_window->get_render());
        SDL_RenderCopy(m_window->get_render(), texture, NULL, &rect);
        SDL_RenderPresent(m_window->get_render());
    }
}

void print_FPS(uint32_t time_since_start, int frames)
{
    int t = SDL_GetTicks();
    float fps = (static_cast<float>(frames) * 1000) / (t - time_since_start);
    std::cout << "Avg FPS: " << std::setprecision(2) << fps << "\n";
}




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
