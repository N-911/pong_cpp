#include "GamePlayController.h"
#include "Settings.h"

GamePlayController::GamePlayController()
{
//    m_score = std::vector<int>(0, 0);
//    m_score_target = 21;
//    m_game_count = 0;
}

void GamePlayController::add_score(int side)
{
    if (side == 0 || side == 1) {
        m_score[side]++;
    }
    else {
        return;
    }
}

void GamePlayController::check_win()
{
    if (m_score[0] >= m_score_target || m_score[1] >= m_score_target) {
        m_game_count++;
    }
    if (m_score[0] >= m_score_target) {
        m_count_win_left++;
        reset_score();
    }
    else if (m_score[1] >= m_score_target) {
        m_count_win_right++;
        reset_score();
    }
}

void GamePlayController::reset_score()
{
    m_score = std::vector<int>(0, 0);
}

GamePlayController::~GamePlayController()
{

}
int GamePlayController::ball_collision(int x, int y)
{
    if (x <= 0) {
        ++m_score[0];
        return 1;
    }
    if (x >= W) {
        ++m_score[1];
        return 0;
    }
    return -1;
}



