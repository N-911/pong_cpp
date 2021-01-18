#ifndef PONG_SRC_GAME_H_
#define PONG_SRC_GAME_H_

#include "Window.h"
#include "Ball.h"
#include "Player.h"
#include <memory>
#include "GamePlayController.h"
#include "GameObjects.h"
#include "Bot.h"
#include "EventManager.h"


enum class GameState {
    MainMenu,
    GameScreen,
    ScoreScreen,
};

class Game {
public:
    Game();
    virtual ~Game();
    void game_loop();

private:
    SDL_Event m_ev;
    std::shared_ptr<EventManager> m_event_manager;
    Window* m_window;
    GameState m_state;
    SDL_bool m_loop;


    int m_frame_count;
    unsigned int m_last_frame;
    int m_fps{0};
    bool m_pause {false};

    std::unique_ptr<Ball> m_ball;
    std::vector<std::unique_ptr<GameObject>> m_game_obj;
//    std::unique_ptr<Bot> m_right;
//  std::unique_ptr<Label>  _scoreLabel;
//  std::unique_ptr<Label> _countdownTimer;
//  std::unique_ptr<Label> _controlsLabel

    std::unique_ptr<GamePlayController> m_game_play;
    SDL_Surface* m_score_surface;
    SDL_Texture* m_score_texture;
    SDL_Color m_text_color;

    SDL_Rect m_score_board;
    int m_number_pl;
//  bool		play_mus;

    int show_menu();
//    void switch_state();
    void on_event(SDL_Event& event);
    void update();
    void render(float interpolation);
    void render_scene();
    void draw_score();
    int check_goal();
};

#endif //PONG_SRC_GAME_H_
