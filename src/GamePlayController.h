#ifndef PONG_SRC_GAMEPLAYCONTROLLER_H_
#define PONG_SRC_GAMEPLAYCONTROLLER_H_
#include <vector>
#include "Settings.h"

class Ball;

class GamePlayController {
public:
    GamePlayController() = default;
    virtual ~GamePlayController();
    void add_score(int side);
    void check_win();
    int ball_collision(int x, int y);

    std::vector<int> get_score() const { return m_score; }

private:
    std::vector<int> m_score{0, 0};

//    int m_winner{-1};
    int m_count_win_right;
    int m_count_win_left;
    int m_game_count{0};
    int m_score_target{11};  // количество очков доя победи
    void reset_score();
};

#endif //PONG_SRC_GAMEPLAYCONTROLLER_H_
